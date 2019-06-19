/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_drop_unnecessary_processes.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 17:29:41 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/11 15:07:20 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "job_control_42.h"

static void	delete_lstfds(t_lstfd *fds)
{
	t_lstfd	*next_fds;

	while (fds != NULL)
	{
		next_fds = fds->next;
		ft_memdel((void **)&(fds));
		fds = next_fds;
	}
}

static void	drop_all_preceeding_processes(t_job *job, t_process *drop_target)
{
	t_process	*next;
	t_process	*to_drop;

	to_drop = job->first_process;
	while (to_drop != drop_target)
	{
		next = to_drop->next;
		delete_lstfds(to_drop->lstfd);
		ft_del_words_tables(&to_drop->argv);
		ft_memdel((void **)&(to_drop));
		to_drop = next;
	}
	job->first_process = drop_target;
}

void		job_drop_unnecessary_processes(t_job *job)
{
	t_process	*drop_target;
	t_process	*current;

	drop_target = NULL;
	current = job->first_process->next;
	while (current != NULL)
	{
		if (current->lstfd != NULL)
		{
			if (current->lstfd->dir == STDIN_FILENO)
				drop_target = current;
		}
		current = current->next;
	}
	if (drop_target != NULL)
		drop_all_preceeding_processes(job, drop_target);
}
