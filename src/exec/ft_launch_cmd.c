/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 16:45:32 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/06 21:58:39 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"
#include "libft.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

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

void		ft_launch_cmd(t_launch **cmd, char ***arge)
{
	if ((*cmd)->argv)
	{
		if ((*cmd)->nbr_pipe)
			ft_launch_pipe(*cmd, arge);
		else
			ft_launch_exe(*cmd, arge);
		ft_free_cmd(*cmd);
		if (!(*cmd = ft_init_cmd(NULL)))
			exit(1);
	}
}
