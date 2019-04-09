/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_job_status.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 16:34:39 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/09 10:16:50 by mmousson         ###   ########.fr       */
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
