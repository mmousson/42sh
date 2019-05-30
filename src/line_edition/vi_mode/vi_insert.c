/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_insert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 15:45:38 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/30 11:02:21 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

int				vi_insert(char *str, int ret)
{
	if (g_env.mode->v_del || g_env.mode->v_visual || g_env.mode->v_yank)
		return (0);
	if (str[0] == 'i' && ret == 1)
		;
	else if (str[0] == 'I' && ret == 1)
		line_cursor_motion(MLEFT, g_env.cm->pos = g_env.p_size);
	else if (str[0] == 'a' && ret == 1)
		line_cursor_motion(MRIGHT, 1);
	else if (str[0] == 'A' && ret == 1)
		line_cursor_motion(MRIGHT, g_env.len - g_env.cm->pos);
	else if (str[0] == 'R' && ret == 1)
	{
		vi_add_undo();
		return (vi_reset_mode(1, 0, 1) + 1);
	}
	else if (str[0] == 'r' && ret == 1)
		return (vi_reset_mode(0, 1, 2) + 1);
	else
		return (0);
	vi_reset_mode(1, 0, 0);
	return (1);
}
