/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_yank.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 14:59:36 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/01 14:24:14 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

void			vi_cpy(void)
{
	int			min;
	int			max;

	if (g_env.cm->pos == g_env.mode->v_pos)
		return ;
	min = g_env.mode->v_pos > g_env.cm->pos ? g_env.cm->pos : g_env.mode->v_pos;
	max = min == g_env.cm->pos ? g_env.mode->v_pos : g_env.cm->pos;
	ft_strncpy(g_env.s_buffer, &(g_env.line[min]), max - min);
	if (g_env.cm->pos == min)
		line_cursor_motion(MRIGHT, max - min);
	else
		line_cursor_motion(MLEFT, max - min);
	vi_reset_mode(0, 1, 0);
}

int				vi_yank(char *str, int ret)
{
	if (g_env.mode->v_del)
		return (0);
	if (str[0] == 'y' && ret == 1)
	{
		if (g_env.mode->v_yank)
		{
			ft_strcpy(g_env.s_buffer, &(g_env.line[g_env.p_size]));
			return (vi_reset_mode(0, 1, 0) + 1);
		}
		g_env.mode->v_yank = 1;
		if (g_env.mode->v_visual)
			vi_cpy();
		g_env.mode->v_pos = g_env.cm->pos;
	}
	else if (str[0] == 'Y' && ret == 1)
		ft_strcpy(g_env.s_buffer, &(g_env.line[g_env.cm->pos]));
	else
		return (0);
	vi_reset_count(str);
	return (1);
}
