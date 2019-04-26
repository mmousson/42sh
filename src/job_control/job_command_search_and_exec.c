/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_command_search_and_exec.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 13:20:38 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/26 14:58:56 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "sh42.h"
#include "libft.h"
#include "job_control_42.h"

/*
**
*/

static int	argc(char **argv)
{
	int	res;

	res = 0;
	while (argv[res] != NULL)
		res++;
	return (res);
}

/*
**
*/

static void	launch_proc(t_job *job, t_process *proc, int fg)
{
	pid_t	pid;

	if ((pid = fork()) == 0)
		child_process(proc, fg, job->pgid);
	else if (pid > 0)
		parent_process(job, proc, pid);
	else
		write(STDERR_FILENO, "Fork Failed\n", 12);
}

/*
**
*/

static void	search_using_path(t_job *job, t_process *proc, int fg)
{
	int		hash;
	char	*to_del;

	to_del = proc->argv[0];
	hash = hash_string(proc->argv[0]);
	if (hash_already_exists(hash, proc->argv[0]))
	{
		g_hash[hash].hits += 1;
		proc->argv[0] = g_hash[hash].full_path;
	}
	else if ((proc->argv[0] = search_utility(proc->argv[0])) == NULL)
	{
		proc->argv[0] = to_del;
		proc->status = 127;
		ft_putstr_fd("42sh: Unknown command ", STDERR_FILENO);
		ft_putendl_fd(to_del, STDERR_FILENO);
		return ;
	}
	ft_strdel(&to_del);
	launch_proc(job, proc, fg);
}

/*
** =================> COMMAND SEARCH AND EXECUTION ALGORITHM <================
*/

void		job_command_search_and_exec(t_job *job, t_process *proc, int fg)
{
	int		p;

	if (ft_strchr(proc->argv[0], '/') != NULL)
		launch_proc(job, proc, fg);
	else
	{
		if ((p = is_builtin(proc->argv[0])) != -1)
			g_builtins[p].handler(argc(proc->argv), proc->argv, proc->environ);
		else
			search_using_path(job, proc, fg);
	}
}
