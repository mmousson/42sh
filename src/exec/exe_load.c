/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 22:40:50 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/07 23:09:49 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"
#include <stdlib.h>
#include "expand.h"

int					is_to_load(int fd)
{
	if (fd > 0 || fd == -3)
		return (1);
	return (0);
}

/*////////// to remove after good red okay
void				print_red(t_launch *cmd_og)
{
	t_lstfd			*tmp;
	t_launch		*cmd;

	cmd = cmd_og;
	while (cmd)
	{
		tmp = cmd->lstfd;
		while (tmp)
		{
			ft_putnbr(tmp->og);ft_putstr(" origin\n");
			ft_putnbr(tmp->dir);ft_putstr(" direction\n");
			if (tmp->close)
				ft_putstr("Closing time..\n");
			tmp = tmp->next;
		}
		ft_putstr("-----------\n");
		cmd = cmd->next;
	}
}
///////// until here*/

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
	proc->name = cmd->argv ? ft_strdup(cmd->argv[0]) : NULL;
	proc->argv = ft_tabdup(cmd->argv);
	//if (expand_manager(&(proc->argv), env))
	//	return (NULL);
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
	ft_launch_red(cmd->red, cmd, env);
	proc->lstfd = cmd->lstfd;
	return (proc);
}

////////// to remove after good red okay
void				print_red_proc(t_process *proc_og)
{
	t_lstfd			*tmp;
	t_process		*proc;

	proc = proc_og;
	while (proc)
	{
		tmp = proc->lstfd;
		while (tmp)
		{
			ft_putnbr(tmp->og);ft_putstr(" origin\n");
			ft_putnbr(tmp->dir);ft_putstr(" direction\n");
			if (tmp->close)
				ft_putstr("Closing time..\n");
			tmp = tmp->next;
		}
		ft_putstr("-----------\n");
		proc = proc->next;
	}
}
///////// until here


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
	//print_red_proc(job->first_process);// will disapear when working
	return (job);	
}
