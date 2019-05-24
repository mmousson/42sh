/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 16:45:32 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/25 00:06:09 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "job_control_42.h"
#include "exe.h"
#include "libft.h"

void		ft_cmd_nf(char *str)
{
	ft_putstr_fd("21sh: command not found: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
}

void		ft_next_pipe(t_launch *cmd)
{
	cmd->next = ft_init_cmd(NULL);
}

void		ft_fork_or_not(t_launch *cmd, char *path, char ***arge)
{
	if (cmd->nbr_pipe)
	{
		execve(path, cmd->argv, *arge);
		exit(1);
	}
	else
		do_fork(path, cmd->argv, *arge);
}

void		ft_launch_exe(t_launch *cmd, char ***arge)
{
	char	*path;
	int		fct;

	path = NULL;
	fct = ft_get_home_cmd(cmd->argv[0]);
	if (fct == 0)
	{
		sh_quiterm();
		exit(0);
	}
	if (!(ft_launch_red(cmd->red, cmd)))
	{
		ft_do_home(fct, cmd->argv, arge);
		if (fct == -1)
		{
			if (ft_path(cmd->argv[0], &path, *arge))
				ft_fork_or_not(cmd, path, arge);
			else
				ft_cmd_nf(cmd->argv[0]);
			if (path)
				free(path);
		}
	}
	ft_res_pile(cmd);
}

// static void print_structures(t_job *job)
// {
// 	t_process *current;

// 	current = job->first_process;
// 	printf("pgid = %d\n", job->pgid);
// 	printf("command = %s\n", job->command);
// 	printf("notified = %d\n", job->notified);
// 	while (current)
// 	{
// 		printf("arguments:\n");
// 		char **tmp = current->argv;
// 		while (*tmp != NULL)
// 		{
// 			printf("%s\n", *tmp);
// 			tmp++;
// 		}
// 		printf("io_channels:\n");
// 		printf("input = %d\n", current->io_channels.input);
// 		printf("output = %d\n", current->io_channels.output);
// 		printf("error = %d\n", current->io_channels.error);
// 		printf("real_channels:\n");
// 		printf("input = %d\n", current->real_channels.input);
// 		printf("output = %d\n", current->real_channels.output);
// 		printf("error = %d\n", current->real_channels.error);
// 		current = current->next;
// 	}

// }

void		ft_launch_cmd(t_launch **cmd, char ***arge, int status)
{
	t_job	*job;
	int		fg;

	// status = PIP + DBL -> ||
	// status = ESP + DBL -> &&
	// status = ESP -> &
	if (status == PIP + DBL && current_ret == 0)
		return ;
	if (status == ESP + DBL && current_ret != 0)
		return ;
	if ((*cmd)->argv)
	{
		fg = status == ESP ? BACKGROUND_LAUNCH : FOREGROUND_LAUNCH;
		job = exe_load_job(*cmd, arge);
		ft_free_cmd(*cmd);
		current_ret = job_launch(job, fg);
		if (!(*cmd = ft_init_cmd(NULL)))
			exit(1);
	}
}
