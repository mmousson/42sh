/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_count.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 17:17:19 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/28 09:05:41 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

int				vi_get_count(char *str)
{
	int			tmp;
	
	if (g_env.mode->v_replace_one)
		return (0);
	tmp = ft_atoi(str);
	if (tmp || (str[0] == '0' && g_env.mode->v_count && !g_env.mode->v_del))
	{
		g_env.mode->v_count = g_env.mode->v_count * 10 + tmp;
		return (1);
	}
	else if (!g_env.mode->v_count)
		g_env.mode->v_count = 1;
	return (0);
}

void			vi_reset_count(char *str)
{
	int			tmp;
	int			i;

	i = -1;
	g_env.mode->saved = 0;
	if (g_env.mode->v_del || g_env.mode->v_yank)
		return ;
	tmp = ft_atoi(str);
	if (!tmp && str[0] != '0' && g_env.mode->v_count)
		g_env.mode->v_count = 0;
}
