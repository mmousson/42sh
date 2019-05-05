/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_setmode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 16:34:56 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/03 11:20:34 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

int					vi_new_mode(t_emode mode)
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
	g_env.count = 0;
	return (0);
}
