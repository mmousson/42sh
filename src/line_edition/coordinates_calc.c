/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinates_calc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 03:23:54 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/25 10:48:45 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

static int	ft_getpos(int pos, int k)
{
	int		x;
	int		i;
	int		max;
	int		len;

	x = 0;
	i = -1;
	max = 1;
	len = (int)ft_strlen(g_env.line);
	while (++i < pos)
	{
		if ((i < len && g_env.line[i] == '\n')
			|| max == g_env.cm->term_x)
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
int			ft_getx(int pos)
{
	return (ft_getpos(pos, 1));
}

int			ft_gety(int pos)
{
	return (ft_getpos(pos, 0));
}

int			ft_get_termroom(void)
{
	return (g_env.cm->term_x * g_env.cm->term_y);
}

int			ft_get_origin_pos(void)
{
	int		room;

	room = ft_get_termroom() - g_env.cm->term_x + ft_getx(g_env.len) + 1;
	return (g_env.len - room + 1);
}
