/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 23:53:08 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/11 13:55:17 by mmousson         ###   ########.fr       */
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
	while (current != NULL && current->pgid != pgid)
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
**	This function is called inside the while loop of the function below
**	It is the one that is actually responsible of freeing all the memory
**	occupied by a 't_process' Data-Structure
**
**	Arguments:
**	to_del -> A pointer to the Data-Structure holding the informations about
**		the process to delete
**
**	Return Value: NONE
*/

static void	job_delete_process(t_process *to_del)
{
	int			i;

	i = -1;
	ft_strdel(&to_del->name);
	if (to_del->argv != NULL)
	{
		while (to_del->argv[++i] != NULL)
			ft_strdel(&to_del->argv[i]);
		ft_strdel(&to_del->argv[i]);
	}
	if (to_del->io_channels.input != STDIN_FILENO)
		close(to_del->io_channels.input);
	if (to_del->io_channels.output != STDOUT_FILENO)
		close(to_del->io_channels.output);
	if (to_del->io_channels.error != STDERR_FILENO)
		close(to_del->io_channels.error);
	ft_memdel((void **)&(to_del->argv));
	ft_memdel((void **)&(to_del));
}

/*
**	Function freeing all allocated data inside a 't_job' Data-Structure
*/

void		job_free(t_job *job)
{
	t_process	*current_process;
	t_process	*next_process;

	remove_job_from_list(job->pgid);
	ft_strdel(&job->command);
	current_process = job->first_process;
	while (current_process != NULL)
	{
		next_process = current_process->next;
		job_delete_process(current_process);
		current_process = next_process;
	}
	ft_memdel((void **)&(job));
}
