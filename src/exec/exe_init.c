/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 18:09:53 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/15 10:38:37 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

t_red			*ft_init_red(void)
{
	t_red		*red;

	if (!(red = (t_red*)malloc(sizeof(t_red))))
		return (NULL);
	red->type = 0;
	red->srt = 0;
	red->close = 0;
	red->end = -1;
	red->lsther = NULL;
	red->end_nm = NULL;
	red->next = NULL;
	return (red);
}

t_launch		*ft_init_cmd(char **argv)
{
	t_launch	*cmd;

	if (!(cmd = (t_launch*)malloc(sizeof(t_launch))))
		return (NULL);
	cmd->nbr_pipe = 0;
	if (!(cmd->red = ft_init_red()))
	{
		ft_memdel((void**)&cmd);
		return (NULL);
	}
	cmd->lstred = NULL;
	cmd->argv = argv;
	cmd->fdpipe = NULL;
	cmd->will_red = 0;
	cmd->dir_creat = 0;
	cmd->in = -2;
	cmd->out = -2;
	cmd->err = -2;
	cmd->next = NULL;
	return (cmd);
}
