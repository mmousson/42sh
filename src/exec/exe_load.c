/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 22:40:50 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/15 17:18:31 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

int					is_to_load(int fd)
{
	if (fd > 0 || fd == -3)
		return (1);
	return (0);
}

t_process			*load_process(t_launch *cmd, char ***env)
{
	t_process		*proc;

	if (!cmd)
		return (NULL);
	if (!(proc = (t_process*)ft_memalloc(sizeof(t_process))))
		return (NULL);
	if (cmd->next)
	{
		if (!(proc->next = load_process(cmd->next, env)))
			return (NULL);
	}
	proc->name = cmd->argv ? ft_strdup(cmd->argv[0]) : NULL;
	proc->argv = ft_tabdup(cmd->argv);
	proc->valid_to_wait_for = true;
	proc->environ = env;
	proc->io_channels.output = 1;
	proc->io_channels.error = 2;
	proc->builtin_bkp.input = -1;
	proc->builtin_bkp.output = -1;
	proc->builtin_bkp.error = -1;
	ft_launch_red(cmd->red, cmd, env);
	proc->lstred = cmd->lstred;
	proc->lstfd = NULL;
	return (proc);
}

t_job				*exe_load_job(t_launch *cmd, char ***arge)
{
	t_job			*job;

	if (!(job = (t_job*)malloc(sizeof(t_job))))
		return (NULL);
	job->pgid = -1;
	job->notified = false;
	job->next = NULL;
	if (!(job->first_process = load_process(cmd, arge)))
	{
		job_free(job);
		return (NULL);
	}
	job->command = ft_strdup(job->first_process->argv[0]);
	return (job);
}
