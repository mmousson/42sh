/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_job_status.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 16:34:39 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/09 23:11:43 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "job_control_42.h"

/*
**	Check for processes that have status information available
**	without blocking
*/

void	update_status (t_job *first_job)
{
	int		status;
	pid_t	pid;

	while (42)
	{
		pid = waitpid (WAIT_ANY, &status, WUNTRACED | WNOHANG);
		if (mark_process_status (first_job, pid, status))
			break ;
	}
}

/*
**
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
