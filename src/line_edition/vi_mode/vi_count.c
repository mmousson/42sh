/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_count.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 17:17:19 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/04 16:38:01 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

int				vi_get_count(char *str)
{
	int			tmp;

	if (g_env.mode->v_replace_one)
		return (0);
	tmp = ft_atoi(str);
	if (g_env.mode->v_command
			&& (tmp || (str[0] == '0' && g_env.count && !g_env.mode->v_del)))
	{
		if (g_env.count * 10 + tmp > BUFF_SIZE)
			return (1);
		g_env.count = g_env.count * 10 + tmp;
		if (!g_env.mode->mode[MVI])
			vi_alloc_count();
		return (1);
	}
	if (!g_env.count)
		g_env.count = 1;
	return (0);
}

void			vi_reset_count(char *str)
{
	int			tmp;

	g_env.mode->saved = 0;
	if (g_env.mode->v_del || g_env.mode->v_yank)
		return ;
	vi_del_count();
	tmp = ft_atoi(str);
	if (!tmp && str[0] != '0' && g_env.count)
		g_env.count = 0;
}
