/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_motion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 22:32:05 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/25 08:52:40 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

static void		ft_cursor_left(void)
{
	g_env.cm->pos--;
}

static void		ft_cursor_right(void)
{
	g_env.cm->pos++;
}

void			ft_cursor_ry(void)
{
	int			len;

	len = (int)ft_strlen(g_env.line);
	ft_cursor_motion(MRIGHT, len - g_env.cm->pos);
	ft_cursor_motion(MLEFT, g_env.cm->pos - len);
}

static int		ft_ismoving(t_move move)
{
	int			len;

	len = (int)ft_strlen(g_env.line);
	if (move == MRIGHT && g_env.cm->pos < len)
		return (1);
	if (move == MLEFT && len > ft_get_termroom()
			&& !g_env.del && !ft_getx(g_env.cm->pos)
			&& g_env.cm->pos < ft_get_origin_pos())
		return (0);
	if (move == MLEFT && g_env.cm->pos > g_env.p_size
			&& (ft_getx(g_env.cm->pos) != 0
				|| ft_gety(g_env.cm->pos) != 0))
		return (1);
	return (0);
}

void			ft_cursor_motion(t_move move, int len)
{
	int			i;

	i = -1;
	while (++i < len)
	{
		if (move == MRIGHT && ft_ismoving(move))
			ft_cursor_right();
		else if (move == MLEFT && ft_ismoving(move))
			ft_cursor_left();
		else if (move == MUP)
			ft_get_uhistory(1);
		else if (move == MDOWN)
			ft_get_dhistory(1);
	}
}
