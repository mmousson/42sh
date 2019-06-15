/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_open_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 10:38:17 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/15 16:01:38 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"
#include "job_control_42.h"

static void		job_open_interrupt(int signo)
{
	(void)signo;
	ft_putendl_fd("\n42sh: open: Interrupted system call", STDERR_FILENO);
}

static t_lstfd	*job_add_lstfd(t_process *process)
{
	t_lstfd	*res;
	t_lstfd	*current;

	if ((res = ft_memalloc(sizeof(t_lstfd))) == NULL)
	{
		ft_putendl_fd("42sh: Internal Malloc Error", STDERR_FILENO);
		return (NULL);
	}
	res->bkp = -1;
	res->og = -1;
	res->dir = -2;
	res->close = 0;
	res->next = NULL;
	current = process->lstfd;
	while (current && current->next)
		current = current->next;
	if (current == NULL)
		process->lstfd = res;
	else
		current->next = res;
	return (res);
}

static int		job_open_files_malloc_fail(t_process *process)
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

static int		job_do_open(t_lstred *current, t_lstfd *fds)
{
	if (current->int_og == 0)
		fds->dir = open(current->name_dir, O_RDONLY);
	else
	{
		if (current->simple == 1)
			fds->dir = open(current->name_dir, O_WRONLY | O_TRUNC | O_CREAT,
				S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
		else if (current->simple == 0)
			fds->dir = open(current->name_dir, O_WRONLY | O_APPEND | O_CREAT,
				S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
	}
	return (fds->dir != -1);
}

int				job_open_files(t_process *process)
{
	t_lstfd		*fds;
	t_lstred	*current;

	current = process->lstred;
	while (current)
	{
		signal(SIGINT, job_open_interrupt);
		if ((fds = job_add_lstfd(process)) == NULL)
			return (job_open_files_malloc_fail(process));
		if (current->close)
			fds->close = 1;
		if (current->int_og >= 0)
			fds->og = current->int_og;
		if (current->int_dir >= 0)
			fds->dir = current->int_dir;
		else if (current->name_dir != NULL)
		{
			if (!job_do_open(current, fds))
				return (job_open_files_malloc_fail(process));
		}
		signal(SIGINT, SIG_DFL);
		current = current->next;
	}
	return (1);
}
