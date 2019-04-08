/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 08:56:30 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/08 08:57:06 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control_42.h"

void	parent_process(t_job *job, pid_t pid)
{
	current_process->pid = pid;
	if (isatty(STDIN_FILENO))
	{
		if (job->pgid == 0)
			job->pgid = pid;
		setpgid(pid, job->pgid);
	}
}
