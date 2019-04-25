/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_edition.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 17:17:19 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/25 10:35:39 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

int				ft_get_count(char *str)
{
	int			tmp;

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

void				ft_reset_count(char *str)
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

int					ft_get_prior_flag(char *str)
{
	int			i;

	i = -1;
	while (++i < 4)
		if (g_env.mode->v_prior[i])
			break ;
	if (i == 4)
		return (0);
	ft_jump_occur(str[0], i, g_env.mode->v_count);
	i = -1;
	g_env.mode->v_lasta = str[0];
	while (++i < 4)
		g_env.mode->v_prior[i] = 0;
	if (g_env.mode->v_del)
		ft_cdel();
	if (g_env.mode->v_yank)
		ft_vi_cpy();
	return (1);
}
