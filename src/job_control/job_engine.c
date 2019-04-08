/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_engine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 02:19:56 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/08 02:19:56 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "job_control_42.h"

/*
**
*/

void					job_launch(t_job *job, int fg)
{
	pid_t		pid;
	t_process	*current_process;

	current_process = job->first_process;
	while (current_process)
	{
		if ((pid = fork()) == 0)
			child_process(current_process, job->pgid, fg);
		else if (pid > 0)
		{

		}
		else
			ft_putendl_fd("Fork Failed", STDERR_FILENO);
		current_process = current_process->next;
	}
}