/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 14:11:12 by hben-yah          #+#    #+#             */
/*   Updated: 2019/06/10 17:10:57 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "cd.h"
#include "libft.h"

static int		is_valid_option(char c, char *options)
{
	if (!ft_isprint(c) || (!ft_strchr(options, c) && c != ' ') || !c)
		return (0);
	return (1);
}

static int		set_options(char *ops, int *options)
{
	int pos;

	pos = 0;
	while (ops[pos])
	{
		if (is_valid_option(ops[pos], "LP"))
		{
			if (ops[pos] == 'L')
				*options = 1;
			else if (ops[pos] == 'P')
				*options = 2;
		}
		else
		{
			ft_putstr_fd(""SH_NAME": cd: illegal option --", 2);
			ft_putchar_fd(ops[pos], 2);
			ft_putendl_fd("\nusage :cd [-LP] [dir]", 2);
			return (1);
		}
		++pos;
	}
	return (0);
}

int				cd_options_parser(char **args, int *options, int *pos_args)
{
	int				i;
	int				takeoptions;

	takeoptions = 1;
	i = 0;
	while (args[++i])
	{
		if (((args[i][0] == '-') && (args[i][1] != '\0')) && takeoptions)
		{
			if (args[i][1] == '-')
				takeoptions = 0;
			else
			{
				if (set_options(args[i] + 1, options) == 1)
					return (1);
			}
		}
		else
		{
			*pos_args = i;
			break ;
		}
	}
	return (0);
}
