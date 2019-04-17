/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 20:54:05 by oboutrol          #+#    #+#             */
/*   Updated: 2019/04/04 13:25:43 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexpars.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

void		ft_pipe_all(int *fdpipe, int nbr_pipes)
{
	int		k;

	k = 0;
	while (k < 2 * nbr_pipes)
	{
		pipe(fdpipe + k);
		k += 2;
	}
}

int			ft_end_of_pipes(int *fdpipe, int nbr_pipes, int status)
{
	int		end;

	ft_pipe_close(fdpipe, nbr_pipes);
	free(fdpipe);
	end = 0;
	while (end <= nbr_pipes)
	{
		wait(&status);
		end++;
	}
	return (nbr_pipes);
}

void		ft_dup_pipe(int *fdpipe, int k, int nbr_pipes)
{
	if (k * 2 - 2 >= 0)
		dup2(fdpipe[k * 2 - 2], 0);
	if (k < nbr_pipes)
		dup2(fdpipe[k * 2 + 1], 1);
}

int			ft_all_pipes(t_cmd *cmd, char ***arge, int nbr_pipes, t_args *args)
{
	int		k;
	int		*fdpipe;
	int		status;

	k = 0;
	status = -2;
	if (!(fdpipe = (int*)malloc(sizeof(int) * 2 * nbr_pipes)))
		return (0);
	ft_pipe_all(fdpipe, nbr_pipes);
	while (k <= nbr_pipes && cmd)
	{
		if (cmd->word)
			if (fork() == 0)
			{
				ft_dup_pipe(fdpipe, k, nbr_pipes);
				ft_pipe_close(fdpipe, nbr_pipes);
				cmd->pipe = 1;
				ft_exec(cmd, arge, args);
				ft_exit_clean_args(args, 0);
			}
		cmd = cmd->next;
		k++;
	}
	return (ft_end_of_pipes(fdpipe, nbr_pipes, status));
}

int			ft_manage_pipe(t_cmd *cmd, char ***arge, t_args *args)
{
	int		nbr_pipes;
	t_cmd	*tmp;

	tmp = cmd;
	nbr_pipes = 0;
	while (cmd && cmd->pipe)
	{
		nbr_pipes++;
		cmd = cmd->next;
	}
	if (nbr_pipes > 0)
		ft_all_pipes(tmp, arge, nbr_pipes, args);
	return (nbr_pipes);
}
