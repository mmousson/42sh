/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_update_job_status.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 16:34:39 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/11 13:57:35 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "libft.h"
#include "job_control_42.h"

#include <errno.h>
#include <stdio.h>

/*
**	Check for processes that have status information available
**	without blocking
*/

void	job_update_status(t_job *first_job)
{
	int			status;
	pid_t		pid;
	t_process	*current;

	if (first_job == NULL)
		return ;
	current = first_job->first_process;
	while (current)
	{
		if (current->completed || current->valid_to_wait_for == false)
		{
			current = current->next;
			continue ;
		}
		pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
		if (job_mark_process_status(pid, status))
			break ;
	}
}

/*
**	This function wakes up a Job and all of its processes
**	It starts by updating the processes' status data to 'stopped=false'
**	Once this is done, it also sets the job's 'notified' value back to false
**	sot the user can be informed of changes of the job's status again
**	Finally, just send the job to the background or background
**	according with the 'foreground' variable
**
**	Arguments:
**	job -> A pointer to Data-Structure representing the
**	foreground -> Boolean value to tell us whether we should re-launch
**		the Job in foreground
*/

void	job_unstop(t_job *job, int foreground)
{
	t_process	*proc;

	proc = job->first_process;
	while (proc)
	{
		proc->stopped = false;
		proc = proc->next;
	}
	job->notified = false;
	if (foreground)
		job_send_to_foreground(job, CONTINUE_JOB);
	else
		job_send_to_background(job, CONTINUE_JOB);
}
