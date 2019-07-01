/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 23:53:08 by mmousson          #+#    #+#             */
/*   Updated: 2019/07/01 14:20:21 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "job_control_42.h"

/*
**	This function deletes a list of redirection 't_lstfd' from a process
**	data-structure
**
**	Arguments:
**	process -> A pointer to the Data-Structure holding all informations
**		about the process from which we want to delete a 't_lstfd'
**
**	Return Value: ALWAYS (-1)
*/

int			job_delete_lstfd(t_process *process)
{
	t_lstfd	*current;
	t_lstfd	*next;

	current = process->lstfd;
	while (current)
	{
		next = current->next;
		ft_memdel((void **)&(current));
		current = next;
	}
	return (-1);
}

/*
**	This function destroys a job's links to the active job list
**	It does nothing if searched pgid is 0, meaning the job we warnt to delete
**	has not been added to the list yet
**
**	Arguments:
**	pgid -> The pgid of the job we want to remove from the active job list
**		and free
**
**	Return Value: NONE
*/

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

static void	job_delete_redirections(t_process *to_del)
{
	t_lstfd		*fds;
	t_lstfd		*next_fds;
	t_lstred	*reds;
	t_lstred	*next_reds;

	fds = to_del->lstfd;
	reds = to_del->lstred;
	while (fds)
	{
		next_fds = fds->next;
		ft_memdel((void **)&(fds));
		fds = next_fds;
	}
	while (reds)
	{
		next_reds = reds->next;
		ft_strdel(&reds->name_og);
		ft_strdel(&reds->name_dir);
		ft_memdel((void **)&(reds));
		reds = next_reds;
	}
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
	int		i;

	i = -1;
	ft_strdel(&to_del->name);
	ft_strdel(&to_del->compound_command);
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
	job_delete_redirections(to_del);
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
