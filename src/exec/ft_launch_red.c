/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_red.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 16:45:02 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/15 17:11:38 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"
#include "libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

static int	make_rel(t_red *red, t_dup *dup, char ***arge)
{
	if (red->type == REL && red->end_nm)
	{
		if (red->end != -1)
		{
			dup->dir = red->end;
			dup->int_dir = red->end;
		}
		else if (!ft_strcmp(red->end_nm, "-") && ((dup->int_dir = -1)))
			red->close = 1;
		else if (!(dup->name_dir = ft_strdup(red->end_nm)))
			return (error_open(red->end_nm));
		dup->simple = 1;
		dup->int_og = 0;
	}
	if (red->type == REL + DBL && red->end_nm)
	{
		ft_heredoc(red->end_nm, arge, red);
		ft_heredoc_read(dup, red);
	}
	return (0);
}

static int	make_rer(t_red *red, t_dup *dup)
{
	if (red->type == RER && red->end_nm)
	{
		if (red->end != -1 && red->end == -2)
			dup->int_dir = 1;
		else if (red->end != -1)
		{
			dup->dir = red->end;
			dup->int_dir = red->end;
		}
		else if (!ft_strcmp(red->end_nm, "-") && ((dup->int_dir = -1)))
			red->close = 1;
		else if (!(dup->name_dir = ft_strdup(red->end_nm)))
			return (error_open(red->end_nm));
		dup->simple = 1;
		dup->int_og = 1;
	}
	if (red->type == RER + DBL && red->end_nm)
	{
		if (!(dup->name_dir = ft_strdup(red->end_nm)))
			return (error_open(red->end_nm));
		dup->int_og = 1;
	}
	return (0);
}

static int	make_one_red(t_red *red, t_launch *cmd, char ***arge)
{
	t_dup	dup;
	int		ret;

	ft_bzero(&dup, sizeof(t_dup));
	dup.int_dir = -2;
	dup.int_og = -2;
	if (!red)
		return (0);
	if ((ret = make_rel(red, &dup, arge)))
		return (ret);
	if ((ret = make_rer(red, &dup)))
		return (ret);
	if (red->srt)
		dup.int_og = red->srt;
	if ((dup.int_dir != -2 || dup.name_dir)
			&& (dup.int_og != -2 || dup.name_og))
		pile_red(&dup, cmd, red->close);
	return (0);
}

int			ft_launch_red(t_red *red, t_launch *cmd, char ***arge)
{
	int		ret;

	ret = 0;
	while (red && !ret)
	{
		ret = make_one_red(red, cmd, arge);
		red = red->next;
	}
	return (ret);
}
