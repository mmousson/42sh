/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 23:53:08 by mmousson          #+#    #+#             */
/*   Updated: 2019/05/10 14:47:40 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "job_control_42.h"

static void	remove_job_from_list(pid_t pgid)
{
	t_job	*previous;
	t_job	*current;

	previous = NULL;
	current = active_job_list;
	while(current != NULL && current->pgid != pgid)
	{
		previous = current;
		current = current->next;
	}
	if (current == NULL)
		return ;
	if (previous != NULL)
		previous->next = current->next;
	else
		active_job_list = current->next;
}

/*
**	Function freeing all allocated data inside a 't_job' Data-Structure
*/

void		job_free(t_job *job)
{
	int			i;
	t_process	*current_process;
	t_process	*next_process;

	remove_job_from_list(job->pgid);
	ft_strdel(&job->command);
	current_process = job->first_process;
	while(current_process != NULL)
	{
		i = -1;
		next_process = current_process->next;
		while(current_process->argv[++i] != NULL)
			ft_strdel(&current_process->argv[i]);
		ft_strdel(&current_process->argv[i]);
		ft_memdel((void **)&(current_process->argv));
		ft_memdel((void **)&(current_process));
		current_process = next_process;
	}
}
