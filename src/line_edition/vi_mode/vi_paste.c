/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_paste.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 15:40:41 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/02 15:04:47 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

static int			vi_ispaste(char *str, int ret)
{
	if ((str[0] == 'p' || str[0] == 'P') && ret == 1)
		return (1);
	return (0);
}

int					vi_paste(char *str, int ret)
{
	if (g_env.mode->v_del || g_env.mode->v_yank)
		return (0);
	if (vi_ispaste(str, ret))
		vi_add_undo();
	if (str[0] == 'p' && ret == 1)
	{
		line_cursor_motion(MRIGHT, 1);
		vi_paste(g_env.s_buffer, g_env.count);
	}
	else if (str[0] == 'P' && ret == 1)
		vi_paste(g_env.s_buffer, g_env.count);
	else
		return (0);
	if (vi_ispaste(str, ret))
		vi_undo_update_pos();
	vi_reset_count(str);
	return (1);
}
