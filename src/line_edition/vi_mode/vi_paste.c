/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_paste.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 15:40:41 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/26 09:37:55 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

static int			ft_vi_ispaste(char *str, int ret)
{
	if ((str[0] == 'p' || str[0] == 'P') && ret == 1)
		return (1);
	return (0);
}

int					ft_vi_paste(char *str, int ret)
{
	if (g_env.mode->v_del || g_env.mode->v_yank)
		return (0);
	if (ft_vi_ispaste(str, ret))
		ft_add_undo();
	if (str[0] == 'p' && ret == 1)
	{
		ft_cursor_motion(MRIGHT, 1);
		ft_paste(g_env.mode->s_buffer, g_env.mode->v_count);
	}
	else if (str[0] == 'P' && ret == 1)
		ft_paste(g_env.mode->s_buffer, g_env.mode->v_count);
	else
		return (0);
	if (ft_vi_ispaste(str, ret))
		ft_undo_update_pos();
	ft_reset_count(str);
	return (1);
}
