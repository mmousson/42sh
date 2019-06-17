/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_open_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 10:38:17 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/17 15:09:10 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __linux__

# include <signal.h>
#endif

#include <fcntl.h>
#include "sh42.h"
#include "libft.h"
#include "job_control_42.h"

int				g_intr = 0;

static void		job_open_interrupt(int signo)
{
	(void)signo;
	g_intr = 1;
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

static void		job_check_file(char *p, int is_input)
{
	int	type;

	if ((type = utility_file_exists(p)) == 0 && is_input)
		ft_putendl3_fd("42sh: ", p, ": No such file or directory", 2);
	else if (type == 0)
		ft_putendl3_fd("42sh: ", p, ": Permission denied", STDERR_FILENO);
	else
	{
		if (type == FILETYPE_DIRECTORY)
			ft_putendl3_fd("42sh: ", p, ": Is a directory", STDERR_FILENO);
		else if (type == FILETYPE_REGULAR)
			ft_putendl3_fd("42sh: ", p, ": Permission denied", STDERR_FILENO);
	}
}

static int		job_do_open(t_lstred *curr, t_lstfd *fds)
{
	if (curr->int_og == 0)
		fds->dir = open(curr->name_dir, O_RDONLY);
	else
	{
		if (curr->simple == 1)
			fds->dir = open(curr->name_dir, O_WRONLY | O_TRUNC | O_CREAT,
				S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
		else if (curr->simple == 0)
			fds->dir = open(curr->name_dir, O_WRONLY | O_APPEND | O_CREAT,
				S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
	}
	if (curr->is_here)
		unlink(curr->name_dir);
	if (!g_intr && fds->dir == -1)
		job_check_file(curr->name_dir, !curr->int_og);
	return (fds->dir != -1);
}

int				job_open_files(t_process *process)
{
	t_lstfd		*fds;
	t_lstred	*current;

	current = process->lstred;
	while (current)
	{
		g_intr = 0;
		signal(SIGINT, job_open_interrupt);
		if ((fds = job_add_lstfd(process)) == NULL)
			return (-1);
		if (current->close)
			fds->close = 1;
		if (current->int_og >= 0)
			fds->og = current->int_og;
		if (current->int_dir >= 0)
			fds->dir = current->int_dir;
		else if (current->name_dir != NULL)
		{
			if (!job_do_open(current, fds))
				return (-1);
		}
		signal(SIGINT, SIG_DFL);
		current = current->next;
	}
	return (1);
}
