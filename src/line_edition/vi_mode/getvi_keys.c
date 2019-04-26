/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getvi_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 16:16:24 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/26 11:43:59 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

int					ft_vi(char *str)
{
	int				i;

	i = -1;
	if (!ft_tmp(str))
		return (0);
	return (1);
}

static int			ft_minsert(char *str, int ret)
{
	int			i;

	i = -1;
	if (str[0] == 27 && ret == 1)
			return (ft_reset_mode(0, 1, 0) + 1);
	if (ft_line_ascii(str, ret))
		return (1);
	else if (ft_line_arrow(str, ret))
		return (1);
	else if (ft_line_history(str))
		return (1);
	return (0);
}

int					ft_line_vi(char *str, int ret)
{
	int				reset;

	reset = 1;
	if (ft_tmp(str) && !g_env.mode->mode[MVI])
		return (0);
	if (str[0] == '\n' && ret == 1)
	{
		ft_bzero(g_env.mode->s_buffer, sizeof(g_env.mode->s_buffer));
		ft_free_undo(g_env.mode->undo);
		g_env.mode->undo = NULL;
		return (ft_reset_mode(1, 0, 0));
	}
	if (g_env.mode->v_insert)
		return (ft_minsert(str, ret));
	else if (g_env.mode->v_command)
		reset = ft_vi_command(str, ret);
	if (!reset)
		return (ft_reset_mode(1, 0, 0));
	return (1);
}
