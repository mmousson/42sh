/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_yank.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 14:59:36 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/26 09:49:13 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

void			ft_vi_cpy(void)
{
	int			min;
	int			max;

	if (g_env.cm->pos == g_env.mode->v_pos)
		return ;
	min = g_env.mode->v_pos > g_env.cm->pos ? g_env.cm->pos : g_env.mode->v_pos;
	max = min == g_env.cm->pos ? g_env.mode->v_pos : g_env.cm->pos;
	ft_strncpy(g_env.mode->s_buffer, &(g_env.line[min]), max - min);
	if (g_env.cm->pos == min)
		ft_cursor_motion(MRIGHT, max - min);
	else
		ft_cursor_motion(MLEFT, max - min);
	ft_reset_mode(0, 1, 0);
}

int				ft_vi_yank(char *str, int ret)
{
	if (g_env.mode->v_del)
		return (0);
	if (str[0] == 'y' && ret == 1)
	{
		if (g_env.mode->v_yank)
		{
			ft_strcpy(g_env.mode->s_buffer, &(g_env.line[g_env.p_size]));
			return (ft_reset_mode(0, 1, 0) + 1);
		}
		g_env.mode->v_yank = 1;
		if (g_env.mode->v_visual)
			ft_vi_cpy();
		g_env.mode->v_pos = g_env.cm->pos;
	}
	else if (str[0] == 'Y' && ret == 1)
		ft_strcpy(g_env.mode->s_buffer, &(g_env.line[g_env.cm->pos]));
	else
		return (0);
	ft_reset_count(str);
	return (1);
}
