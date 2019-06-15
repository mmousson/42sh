/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_parent_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 21:52:44 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/15 13:48:12 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "job_control_42.h"

void	job_parent_process(t_job *job, t_process *proc, pid_t pid)
{
	proc->pid = pid;
	if (isatty(STDIN_FILENO))
	{
		if (job->pgid == -1)
			job->pgid = pid;
		setpgid(pid, job->pgid);
	}
}
