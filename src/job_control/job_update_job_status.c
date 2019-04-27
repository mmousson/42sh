/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_job_status.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 16:34:39 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/10 05:38:10 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "job_control_42.h"

#include <errno.h>
#include <stdio.h>

/*
**	Check for processes that have status information available
**	without blocking
*/

void	update_status (t_job *first_job)
{
	int			status;
	pid_t		pid;
	t_process	*current;

	current = first_job->first_process;
	while (current)
	{
		if (current->completed)
		{
			current = current->next;
			continue ;
		}
		pid = waitpid (WAIT_ANY, &status, WUNTRACED | WNOHANG);
		if (mark_process_status (first_job, pid, status))
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

void	unstop_job(t_job *job, int foreground)
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
		send_job_to_foreground(job, CONTINUE_JOB);
	else
		send_job_to_background(job, CONTINUE_JOB);
}
