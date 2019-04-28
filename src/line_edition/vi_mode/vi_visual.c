/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_visual.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 15:43:11 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/27 11:29:01 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

int			vi_visual(char *str, int ret)
{
	if (g_env.mode->v_del || g_env.mode->v_yank)
		return (0);
	if (str[0] == 'v' && ret == 1)
	{
		if (g_env.mode->v_visual)
			return (vi_reset_mode(0, 1, 0) + 1);
		g_env.mode->v_visual = 1;
		g_env.mode->v_pos = g_env.cm->pos;
	}
	else
		return (0);
	vi_reset_count(str);
	return (1);
}
