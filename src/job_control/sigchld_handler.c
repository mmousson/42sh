/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigchld_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 02:05:35 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/10 03:51:42 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include "libft.h"
#include "job_control_42.h"

void		first_job_set_and_get(t_job **to_set_or_get, int set_or_get)
{
	static t_job	*first_job = NULL;

	if (set_or_get == SET)
	{
		if (to_set_or_get == NULL || *to_set_or_get == NULL)
			return ;
		first_job = *to_set_or_get;
	}
	else if (set_or_get == GET)
	{
		if (to_set_or_get == NULL)
			return ;
		*to_set_or_get = first_job;
	}
}

#ifdef SIGCHLD

void		sigchld_handler(int signo)
{
	t_job	*current;
	t_job	*job_next;
	t_job	*job_last;

	first_job_set_and_get(&current, GET);
	update_status(current);
	job_last = NULL;
	if (signo == SIGCHLD)
	{
		while (current)
		{
			job_next = current->next;
			if (job_is_completed(current))
			{
				inform_user_about_job_completion(current, "completed");
				if (job_last)
					job_last->next = job_next;
				else
					first_job_set_and_get(&job_next, SET);
			}
			else if (job_is_stopped(current))
			{
				inform_user_about_job_completion(current, "stopped");
				job_last = current;
			}
			else
				job_last = current;
			current = job_next;
		}
	}
}
#endif
