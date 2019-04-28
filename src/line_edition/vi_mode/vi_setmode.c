/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_setmode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 16:34:56 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/27 20:22:12 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

static int			vi_new_mode(t_emode mode)
{
	int				i;

	i = 0;
	while (i < MODE)
	{
		if (i == mode)
			g_env.mode->mode[i] = 1;
		else
			g_env.mode->mode[i] = 0;
		i++;
	}
	g_env.mode->n_select = 0;
	if (mode == MVI)
		g_env.mode->v_insert = 1;
	return (1);
}

int					line_vi_tmp(char *str)
{
	if (str[0] == -62 && str[1] == -70)
		return (vi_new_mode(MNORMAL));
	else if (str[0] == -30 && str[1] == -128 && str[2] == -109)
		return (vi_new_mode(MVI));
	return (0);
}

int					vi_reset_mode(int ins, int com, int replace)
{
	int				i;

	i = -1;
	if (!g_env.mode->mode[MVI])
		return (0);
	g_env.mode->v_replace = replace;
	g_env.mode->v_replace_one = replace == 2 ? 1 : 0;
	g_env.mode->v_del = 0;
	g_env.mode->v_insert = ins;
	g_env.mode->v_command = com;
	g_env.mode->v_visual = 0;
	g_env.mode->v_yank = 0;
	while (++i < 4)
		g_env.mode->v_prior[i] = 0;
	if (g_env.mode->v_replace_one)
		return (0);
	g_env.mode->v_count = 0;
	return (0);
}
