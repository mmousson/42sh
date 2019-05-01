/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_cpy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 02:36:49 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/01 14:37:45 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

void				line_init_cpy(void)
{
	g_env.mode->n_select = 1;
	g_env.cpos = g_env.cm->pos;
}

void				line_escap_cpy(int move_cursor)
{
	g_env.mode->n_select = 0;
	if (!move_cursor || g_env.cm->pos == g_env.cpos)
		return ;
	if (g_env.cm->pos < g_env.cpos)
		line_cursor_motion(MRIGHT, g_env.cpos - g_env.cm->pos);
	else
		line_cursor_motion(MLEFT, g_env.cm->pos - g_env.cpos);
}

static void			line_ccpy(int ctrlc)
{
	int				min;
	int				max;

	if (g_env.cm->pos == g_env.cpos)
		return ;
	min = g_env.cpos > g_env.cm->pos ? g_env.cm->pos : g_env.cpos;
	max = min == g_env.cm->pos ? g_env.cpos : g_env.cm->pos;
	ft_strncpy(g_env.s_buffer, &(g_env.line[min]), max - min);
	if (ctrlc)
		line_escap_cpy(1);
}

static void			line_cut(void)
{
	if (g_env.cm->pos == g_env.cpos)
		return ;
	line_ccpy(0);
	if (g_env.cpos < g_env.cm->pos)
	{
		g_env.line = line_delchar(g_env.cm->pos - g_env.cpos);
		line_cursor_motion(MLEFT, g_env.cpos - g_env.cm->pos);
		line_escap_cpy(1);
	}
	else
	{
		g_env.line = line_delchar_bs(g_env.cpos - g_env.cm->pos);
		line_cursor_motion(MLEFT, g_env.cm->pos - g_env.cpos);
		line_escap_cpy(0);
	}
}

int					line_cpy(char *str, int ret)
{
	if (str[0] == 27 && ret == 1)
		line_escap_cpy(1);
	else if (line_isaltc(str, ret))
		line_ccpy(1);
	else if (line_isaltx(str, ret))
		line_cut();
	line_motion(str, ret);
	return (1);
}
