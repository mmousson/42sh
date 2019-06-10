/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_red.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 16:45:02 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/10 14:34:17 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"
#include "libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

static int	make_rel(t_red *red, t_dup *dup, char ***arge, t_launch *cmd)
{
	if (red->type == REL && red->end_nm)
	{
		if (red->end != -1)
			dup->dir = red->end;
		else if ((dup->dir = open(red->end_nm, O_RDONLY)) == -1)
			return (error_open(red->end_nm));
		if (red->end != -1)
			cmd->dir_creat = 1;
		dup->og = 0;
	}
	if (red->type == REL + DBL && red->end_nm)
	{
		ft_heredoc(red->end_nm, arge, red);
		ft_heredoc_read(&dup->og, &dup->dir, red);
	}
	return (0);
}

static int	make_rer(t_red *red, t_dup *dup, t_launch *cmd)
{
	if (red->type == RER && red->end_nm)
	{
		if (red->end != -1 && red->end == -2)
			dup->dir = 1;
		else if (red->end != -1)
			dup->dir = red->end;
		else if (!ft_strcmp(red->end_nm, "-") && ((dup->dir = -1)))
			red->close = 1;
		else if ((dup->dir = open(red->end_nm, O_WRONLY | O_TRUNC | O_CREAT,
					S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR)) == -1)
			return (error_open(red->end_nm));
		if (dup->dir != 1)
			cmd->dir_creat = 1;
		dup->og = 1;
	}
	if (red->type == RER + DBL && red->end_nm)
	{
		if ((dup->dir = open(red->end_nm, O_WRONLY | O_APPEND | O_CREAT,
					S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR)) == -1)
			return (error_open(red->end_nm));
		cmd->dir_creat = 1;
		dup->og = 1;
	}
	return (0);
}

static int	make_one_red(t_red *red, t_launch *cmd, char ***arge)
{
	t_dup	dup;
	int		ret;

	dup.dir = -2;
	dup.og = -2;
	if (!red)
		return (0);
	if ((ret = make_rel(red, &dup, arge, cmd)))
		return (ret);
	if ((ret = make_rer(red, &dup, cmd)))
		return (ret);
	if (red->srt)
		dup.og = red->srt;
	if (dup.dir != -2 && dup.og != -2)
	{
		ft_add_pile(dup.og, dup.dir, cmd, red->close);
	}
	return (0);
}

int			ft_launch_red(t_red *red, t_launch *cmd, char ***arge)
{
	t_red	*tmp;
	int		ret;

	ret = 0;
	tmp = red;
	while (red && !ret)
	{
		ret = make_one_red(red, cmd, arge);
		red = red->next;
	}
	red = tmp;
	return (ret);
}
