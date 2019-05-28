/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_curmotion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 22:32:05 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/28 16:16:20 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

static void		line_cursor_left(void)
{
	g_env.cm->pos--;
}

static void		line_cursor_right(void)
{
	g_env.cm->pos++;
}

void			line_cursor_ry(void)
{
	int			len;

	len = (int)ft_strlen(g_env.line);
	line_cursor_motion(MRIGHT, len - g_env.cm->pos);
	line_cursor_motion(MLEFT, g_env.cm->pos - len);
}

static int		line_ismoving(t_move move)
{
	int			len;

	len = (int)ft_strlen(g_env.line);
	if (move == MRIGHT && g_env.cm->pos < len)
		return (1);
	if (move == MLEFT && len > line_get_termroom()
			&& !g_env.del && !line_getx(g_env.cm->pos)
			&& g_env.cm->pos < line_get_origin_pos())
		return (0);
	if (move == MLEFT && g_env.cm->pos > g_env.p_size
			&& (line_getx(g_env.cm->pos) != 0
				|| line_gety(g_env.cm->pos) != 0))
		return (1);
	return (0);
}

void			line_cursor_motion(t_move move, int len)
{
	int			i;

	i = -1;
	while (++i < len)
	{
		if (move == MRIGHT && line_ismoving(move))
			line_cursor_right();
		else if (move == MLEFT && line_ismoving(move))
			line_cursor_left();
		else if (move == MUP)
			line_get_uhistory(1);
		else if (move == MDOWN)
			line_get_dhistory(1);
	}
}
