/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 22:40:50 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/28 16:54:23 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"
#include <stdlib.h>
#include "expand.h"

t_io_channels		cmd_red(t_launch *cmd)
{
	t_io_channels	chan;

	ft_launch_red(cmd->red, cmd);
	chan.input = cmd->in < 0 ? 0 : cmd->in;
	chan.output = cmd->out < 0 ? 1 : cmd->out;
	chan.error = cmd->err < 0 ? 2 : cmd->err;
	return (chan);
}

t_io_channels		pip_red(t_process *first)//toujours utile ?
{
	t_io_channels	chan;
	
	if (first)
		chan.input = first->real_channels.input;
	else
		chan.input = 0;
	while (first && first->next)
		first = first->next;
	if (first)
	{
		chan.output = first->real_channels.output;
		chan.error = first->real_channels.error;
	}
	else
	{
		chan.output = 1;
		chan.error = 2;
	}
	return (chan);
}

t_process			*load_process(t_launch *cmd, char ***env)
{
	t_process		*proc;

	if (!cmd)
		return (NULL);
	if (!(proc = (t_process*)malloc(sizeof(t_process))))
		return (NULL);
	if (cmd->next)
	{
		if (!(proc->next = load_process(cmd->next, env)))
			return (NULL);
	}
	else
		proc->next = NULL;
	proc->argv = ft_tabdup(cmd->argv);
	if (expand_manager(&(proc->argv), env))
		return (NULL);
	proc->completed = false;
	proc->stopped = false;
	proc->valid_to_wait_for = true;
	proc->environ = env;
	proc->io_channels.input = 0;
	proc->io_channels.output = 1;
	proc->io_channels.error = 2;
	proc->builtin_bkp.input = -1;
	proc->builtin_bkp.output = -1;
	proc->builtin_bkp.error = -1;
	proc->real_channels = cmd_red(cmd);
	return (proc);
}

t_job				*exe_load_job(t_launch *cmd, char ***arge)
{
	t_job			*job;

	if (!(job = (t_job*)malloc(sizeof(t_job))))
		return (NULL);
	job->pgid = 0;
	job->notified = false;
	job->next = NULL;
	if (!(job->first_process = load_process(cmd, arge)))
		return (NULL);
	job->command = ft_strdup(job->first_process->argv[0]);
	return (job);	
}
