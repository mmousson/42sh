/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 18:49:54 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/06 22:10:20 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

static void		ft_pipe_all(int *fdpipe, int nbr_pipes)
{
	int			k;

	k = 0;
	while (k < 2 * nbr_pipes)
	{
		pipe(fdpipe + k);
		k += 2;
	}
}

static void		ft_dup_pipe(int *fdpipe, int k, int nbr_pipes)
{
	if (k * 2 - 2 >= 0)
		dup2(fdpipe[k * 2 - 2], 0);
	if (k < nbr_pipes)
		dup2(fdpipe[k * 2 + 1], 1);
}

void			ft_launch_pipe(t_launch *cmd, char ***arge)
{
	t_launch	*tmp;
	int			k;

	tmp = cmd;
	if (!(cmd->fdpipe = (int*)malloc(sizeof(int) * 2 * cmd->nbr_pipe)))
		return ;
	ft_pipe_all(cmd->fdpipe, cmd->nbr_pipe);
	k = 0;
	while (k <= cmd->nbr_pipe && tmp)
	{
		if (tmp->argv)
			if (fork() == 0)
			{
				//sig_setchild(1);
				ft_dup_pipe(cmd->fdpipe, k, cmd->nbr_pipe);
				ft_pipe_close(cmd->fdpipe, cmd->nbr_pipe);
				ft_launch_exe(tmp, arge);
				sh_quiterm();
			}
		tmp = tmp->next;
		if (tmp)
			tmp->nbr_pipe = cmd->nbr_pipe;
		k++;
	}
	ft_end_of_pipes(cmd->fdpipe, cmd->nbr_pipe);
}
