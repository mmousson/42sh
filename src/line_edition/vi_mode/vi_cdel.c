/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_cdel.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 15:34:42 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/03 10:04:08 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

void			vi_cdel(void)
{
	if (g_env.mode->v_del)
		vi_add_undo();
	if (g_env.mode->v_pos == g_env.cm->pos)
		return ;
	if (g_env.mode->v_pos < g_env.cm->pos)
	{
		g_env.line = line_delchar(g_env.cm->pos - g_env.mode->v_pos);
		line_cursor_motion(MLEFT, g_env.cm->pos - g_env.mode->v_pos);
	}
	else
		g_env.line = line_delchar_bs(g_env.mode->v_pos - g_env.cm->pos - 1);
	g_env.mode->v_del = 0;
	g_env.mode->v_pos = 0;
	vi_undo_update_pos();
	vi_reset_mode(1, 0, 0);
}
