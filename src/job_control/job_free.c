/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 23:53:08 by mmousson          #+#    #+#             */
/*   Updated: 2019/05/30 16:25:35 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "job_control_42.h"

static void	remove_job_from_list(pid_t pgid)
{
	t_job	*previous;
	t_job	*current;

	previous = NULL;
	current = g_active_job_list;
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
		g_active_job_list = current->next;
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
		ft_strdel(&current_process->name);
		while(current_process->argv[++i] != NULL)
			ft_strdel(&current_process->argv[i]);
		if (current_process->io_channels.input != STDIN_FILENO)
			close(current_process->io_channels.input);
		if (current_process->io_channels.output != STDOUT_FILENO)
			close(current_process->io_channels.output);
		if (current_process->io_channels.error != STDERR_FILENO)
			close(current_process->io_channels.error);
		if (current_process->real_channels.input != STDIN_FILENO)
			close(current_process->real_channels.input);
		if (current_process->real_channels.output != STDOUT_FILENO)
			close(current_process->real_channels.output);
		if (current_process->real_channels.error != STDERR_FILENO)
			close(current_process->real_channels.error);
		ft_strdel(&current_process->argv[i]);
		ft_memdel((void **)&(current_process->argv));
		ft_memdel((void **)&(current_process));
		current_process = next_process;
	}
	ft_memdel((void **)&(job));
}
