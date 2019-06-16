/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_sigterm_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 14:40:07 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/16 14:40:07 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <signal.h>
#include <unistd.h>
#include "sh42.h"
#include "libft.h"
#include "job_control_42.h"

static void	job_signal_all_processes(int signal)
{
	t_job		*next_job;
	t_job		*current_job;
	t_process	*current_process;

	current_job = g_active_job_list;
	while (current_job != NULL)
	{
		next_job = current_job->next;
		current_process = current_job->first_process;
		while (current_process != NULL)
		{
			kill(current_process->pid, SIGTERM);
			current_process = current_process->next;
		}
		if (signal == SIGKILL)
			job_free(current_job);
		current_job = next_job;
	}
}

void		job_sigterm(int signo)
{
	time_t	seconds;

	(void)signo;
	ft_putendl("\n42sh: Received deadly signal SIGTERM");
	seconds = time(NULL) + (time_t)10;
	ft_putendl("Sending SIGTERM to all processes...");
	job_signal_all_processes(SIGTERM);
	while (time(NULL) != seconds)
		;
	ft_putendl("Sending SIGKILL to all processes...");
	job_signal_all_processes(SIGKILL);
	ft_putendl("Exiting...");
	blt_exit(1, NULL, NULL);
}
