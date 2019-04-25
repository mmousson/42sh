/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_cdel.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 15:34:42 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/25 10:26:07 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

void			ft_cdel(void)
{
	if (g_env.mode->v_pos == g_env.cm->pos)
		return ;
	if (g_env.mode->v_pos < g_env.cm->pos)
	{
		g_env.line = ft_delchar(g_env.cm->pos - g_env.mode->v_pos);
		ft_cursor_motion(MLEFT, g_env.cm->pos - g_env.mode->v_pos);
	}
	else
		g_env.line = ft_delchar_bs(g_env.mode->v_pos - g_env.cm->pos);
	if (g_env.mode->v_del)
		ft_add_undo();
	g_env.mode->v_del = 0;
	g_env.mode->v_pos = 0;
	ft_reset_mode(1, 0);
}
