/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_red.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 00:10:33 by oboutrol          #+#    #+#             */
/*   Updated: 2019/04/03 17:15:07 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexpars.h"
#include "libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

int			esperl(t_word *red, int dir, int og, t_args *arg)
{
	if (red->type % 10 == 2)
	{
		if (og < 0)
			og = 1;
		if (!ft_strcmp(red->value, "-"))
		{
			ft_add_pile(og, arg);
			close(og);
			return (0);
		}
		else
			dir = ft_atoi(red->value);
	}
	if (og >= 0 && dir >= 0)
	{
		ft_add_pile(og, arg);
		dup2(dir, og);
	}
	return (0);
}

int			aggregate(t_word *red, int dir, int og, t_args *arg)
{
	if (red->type >= 10)
		og = red->type / 10;
	return (esperl(red, dir, og, arg));
}

int			double_red(t_word *red, int dir, int og, t_args *args)
{
	if (red->type % 10 == 5)
	{
		ft_heredoc(args, red->value);
		return (0);
	}
	if (red->type % 10 == 6)
	{
		if ((dir = open(red->value, O_WRONLY | O_CREAT | O_APPEND,
				S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR)) == -1)
			return (error_open(red->value));
		og = 1;
	}
	return (aggregate(red, dir, og, args));
}

int			make_one_red(t_word *red, t_args *args)
{
	int		dir;
	int		og;

	dir = -2;
	og = -2;
	if (!red)
		return (0);
	if (red->type % 10 == 3)
	{
		if ((dir = open(red->value, O_RDONLY)) == -1)
			return (error_open(red->value));
		og = 0;
	}
	else if (red->type % 10 == 4)
	{
		if ((dir = open(red->value, O_WRONLY | O_TRUNC | O_CREAT,
				S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR)) == -1)
			return (error_open(red->value));
		og = 1;
	}
	return (double_red(red, dir, og, args));
}

int			ft_launch_red(t_word *red, t_args *args)
{
	t_word	*tmp;
	int		ret;

	ret = 0;
	tmp = red;
	while (red && !ret)
	{
		ret = make_one_red(red, args);
		red = red->next;
	}
	red = tmp;
	return (ret);
}
