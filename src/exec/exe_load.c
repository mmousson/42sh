/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 22:40:50 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/10 16:34:40 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"
#include <stdlib.h>

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
	proc->next = load_process(cmd->next, env);
	proc->argv = ft_tabdup(cmd->argv);
	proc->completed = false;
	proc->stopped = false;
	proc->valid_to_wait_for = true;
	proc->environ = env;
	proc->io_channels.input = 0;
	proc->io_channels.output = 1;
	proc->io_channels.error = 2;
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
	job->env = arge;
	job->next = NULL;
	job->first_process = load_process(cmd, arge);
	job->io_channels = pip_red(job->first_process);
	job->command = ft_strdup(job->first_process->argv[0]);
	return (job);	
}