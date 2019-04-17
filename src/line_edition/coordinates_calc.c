/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinates_calc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 03:23:54 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/06 19:10:48 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"
#include "libft.h"

static int	ft_getpos(t_env *env, int pos, int k)
{
	int		x;
	int		i;
	int		max;
	int		len;

	x = 0;
	i = -1;
	max = 1;
	len = (int)ft_strlen(env->line);
	while (++i < pos)
	{
		if ((i < len && env->line[i] == '\n')
			|| max == env->cm->term_x)
		{
			max = 1;
			x = k ? 0 : x + 1;
		}
		else
		{
			max++;
			x = k ? x = 1 : x;
		}
	}
	return (x);
}
int			ft_getx(t_env *env, int pos)
{
	return (ft_getpos(env, pos, 1));
}

int			ft_gety(t_env *env, int pos)
{
	return (ft_getpos(env, pos, 0));
}

int			ft_get_termroom(t_env *env)
{
	return (env->cm->term_x * env->cm->term_y);
}

int			ft_get_origin_pos(t_env *env)
{
	int		room;

	room = ft_get_termroom(env) - env->cm->term_x + ft_getx(env, env->len) + 1;
	return (env->len - room + 1);
}
