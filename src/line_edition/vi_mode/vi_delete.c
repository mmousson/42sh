/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_delete.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 19:54:00 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/03 10:07:40 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

static void		vi_delall_line(void)
{
	g_env.mode->v_pos = g_env.len;
	line_home(1);
	vi_cdel();
}

static void		vi_isdelete(char *str, int ret, int start)
{
	if (!g_env.mode->v_del && (str[0] == 'c' || str[0] == 'd'
				|| str[0] == 'C' || str[0] == 'D' || str[0] == 'S'
				|| str[0] == 'x' || str[0] == 'X') && ret == 1)
	{
		if (start)
			vi_add_undo();
		else
			vi_undo_update_pos();
	}
}

static int		vi_delete3(char *str, int ret)
{
	if (str[0] == 'S' && ret == 1)
	{
		g_env.mode->v_del++;
		vi_delall_line();
	}
	else if (str[0] == 'x' && ret == 1)
	{
		g_env.mode->saved = 1;
		if (g_env.mode->v_visual)
			vi_cdel();
		g_env.line = line_delchar_bs(g_env.count);
	}
	else if (str[0] == 'X' && ret == 1)
	{
		g_env.mode->saved = 1;
		if (g_env.mode->v_visual)
			vi_cdel();
		g_env.line = line_delchar(g_env.count);
		line_cursor_motion(MLEFT, g_env.count);
	}
	else
		return (0);
	vi_isdelete(str, ret, 0);
	vi_reset_count(str);
	return (1);
}

static int		vi_delete2(char *str, int ret)
{
	if ((str[0] == 'C' || str[0] == 'D') && ret == 1)
	{
		if (str[0] == 'D')
			g_env.mode->saved = 1;
		g_env.mode->v_pos = g_env.cm->pos;
		line_end();
		vi_cdel();
	}
	else if (!g_env.mode->v_del)
		return (vi_delete3(str, ret));
	vi_isdelete(str, ret, 0);
	vi_reset_count(str);
	return (1);
}

int				vi_delete(char *str, int ret)
{
	vi_isdelete(str, ret, 1);
	if ((str[0] == 'c' || str[0] == 'd') && ret == 1)
	{
		if (str[0] == 'd')
			g_env.mode->saved = 1;
		if (g_env.mode->v_visual)
			vi_cdel();
		g_env.mode->v_del++;
		g_env.mode->v_pos = g_env.cm->pos;
		if (g_env.mode->v_del == 2)
			vi_delall_line();
	}
	else if (!g_env.mode->v_del)
		return (vi_delete2(str, ret));
	vi_isdelete(str, ret, 0);
	vi_reset_count(str);
	return (1);
}
