/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_red.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 16:45:02 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/06 03:35:38 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"
#include "libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

static int	make_rel(t_red *red, int *og, int *dir, char ***arge)
{
	if (red->type == REL && red->end_nm)
	{
		if (red->end != -1)
			*dir = red->end;
		else if ((*dir = open(red->end_nm, O_RDONLY)) == -1)
			return (error_open(red->end_nm));
		*og = 0;
	}
	if (red->type == REL + DBL && red->end_nm)
	{
		ft_heredoc(red->end_nm, arge);
		ft_heredoc_read(og, dir);
	}
	return (0);
}

static int	make_rer(t_red *red, int *og, int *dir)
{
	if (red->type == RER && red->end_nm)
	{
		if (red->end != -1)
		{
			if (red->end == -2)
				*dir = 1;
			else
				*dir = red->end;
		}
		else if (!ft_strcmp(red->end_nm, "-"))
		{
			*dir = -1;
			red->close = 1;
		}
		else if ((*dir = open(red->end_nm, O_WRONLY | O_TRUNC | O_CREAT,
					S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR)) == -1)
			return (error_open(red->end_nm));
		*og = 1;
	}
	if (red->type == RER + DBL && red->end_nm)
	{
		if ((*dir = open(red->end_nm, O_WRONLY | O_APPEND | O_CREAT,
					S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR)) == -1)
			return (error_open(red->end_nm));
		*og = 1;
	}
	return (0);
}
/*
static int	bad_fd(int dir)
{
	ft_putstr_fd("42sh: ", 2);
	ft_putnbr_fd(dir, 2);
	ft_putstr_fd(": bad file descriptor\n", 2);
	return (1);
}
*/
static int	make_one_red(t_red *red, t_launch *cmd, char ***arge)
{
	int		dir;
	int		og;
	int		ret;

	dir = -2;
	og = -2;
	if (!red)
		return (0);
	if ((ret = make_rel(red, &og, &dir, arge)))
		return (ret);
	if ((ret = make_rer(red, &og, &dir)))
		return (ret);
	if (red->srt)
		og = red->srt;
	if (dir != -2 && og != -2)
	{
		ft_add_pile(og, dir, cmd, red->close);
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
