/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_paste.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 15:40:41 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/25 10:37:54 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

int					ft_vi_paste(char *str, int ret)
{
	if (g_env.mode->v_del || g_env.mode->v_yank)
		return (0);
	if (str[0] == 'p' && ret == 1)
	{
		ft_cursor_motion(MRIGHT, 1);
		ft_paste(g_env.mode->s_buffer, g_env.mode->v_count);
	}
	else if (str[0] == 'P' && ret == 1)
		ft_paste(g_env.mode->s_buffer, g_env.mode->v_count);
	else
		return (0);
	ft_add_undo();
	ft_reset_count(str);
	return (1);
}
