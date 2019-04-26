/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_delete.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 19:54:00 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/26 10:02:32 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

static void		ft_delall_line(void)
{
	g_env.mode->v_pos = g_env.len;
	ft_home(1);
	ft_cdel();
}

static void		ft_isdelete(char *str, int ret, int start)
{
		if (!g_env.mode->v_del && (str[0] == 'c' || str[0] == 'd'
					|| str[0] == 'C' || str[0] == 'D' || str[0] == 'S'
					|| str[0] == 'x' || str[0] == 'X') && ret == 1)
		{
			if (start)
				ft_add_undo();
			else
				ft_undo_update_pos();
		}
}

static int		ft_vi_delete3(char *str, int ret)
{
	if (str[0] == 'S' && ret == 1)
	{
		g_env.mode->v_del++;
		ft_delall_line();
	}
	else if (str[0] == 'x' && ret == 1)
	{
		g_env.mode->saved = 1;
		if (g_env.mode->v_visual)
			ft_cdel();
		g_env.line = ft_delchar_bs(g_env.mode->v_count);
	}
	else if (str[0] == 'X' && ret == 1)
	{
		g_env.mode->saved = 1;
		if (g_env.mode->v_visual)
			ft_cdel();
		g_env.line = ft_delchar(g_env.mode->v_count);
		ft_cursor_motion(MLEFT, g_env.mode->v_count);
	}
	else
		return (0);
	ft_isdelete(str, ret, 0);
	ft_reset_count(str);
	return (1);
}

static int		ft_vi_delete2(char *str, int ret)
{
	if ((str[0] == 'C' || str[0] == 'D') && ret == 1)
	{
		if (str[0] == 'D')
			g_env.mode->saved = 1;
		g_env.mode->v_pos = g_env.cm->pos;
		ft_end();
		ft_cdel();
	}
	else if (!g_env.mode->v_del)
		return (ft_vi_delete3(str, ret));
	ft_isdelete(str, ret, 0);
	ft_reset_count(str);
	return (1);
}

int				ft_vi_delete(char *str, int ret)
{
	ft_isdelete(str, ret, 1);
	if ((str[0] == 'c' || str[0] == 'd') && ret == 1)
	{
		if (str[0] == 'd')
			g_env.mode->saved = 1;
		if (g_env.mode->v_visual)
			ft_cdel();
		g_env.mode->v_del++;
		g_env.mode->v_pos = g_env.cm->pos;
		if (g_env.mode->v_del == 2)
			ft_delall_line();
	}
	else if (!g_env.mode->v_del)
		return (ft_vi_delete2(str, ret));
	ft_isdelete(str, ret, 0);
	ft_reset_count(str);
	return (1);
}
