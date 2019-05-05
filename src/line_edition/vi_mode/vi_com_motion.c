/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_com_motion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 13:20:36 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/03 11:56:27 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

static int			vi_priorjump(char *str, int ret)
{
	if (str[0] == 'f' && ret == 1)
		g_env.mode->v_prior[0] = 1;
	else if (str[0] == 'F' && ret == 1)
		g_env.mode->v_prior[1] = 1;
	else if (str[0] == 't' && ret == 1)
		g_env.mode->v_prior[2] = 1;
	else if (str[0] == 'T' && ret == 1)
		g_env.mode->v_prior[3] = 1;
	else
		return (0);
	g_env.mode->v_lastc = str[0];
	return (1);
}

static int			vi_spec_motion(char *str, int ret)
{
	if (str[0] == '^' && ret == 1)
		line_home(0);
	else if (str[0] == '$' && ret == 1)
		line_end();
	else if (str[0] == '0' && ret == 1)
		line_home(1);
	else if (str[0] == '|' && ret == 1)
		vi_pipejump(g_env.count);
	else if (str[0] == ';' && ret == 1)
		vi_repeat();
	else if (str[0] == ',' && ret == 1)
		vi_rev_repeat();
	else
		return (0);
	if (g_env.mode->v_del)
		vi_cdel();
	if (g_env.mode->v_yank)
		vi_cpy();
	vi_reset_count(str);
	return (1);
}

int					vi_motion(char *str, int ret)
{
	if (vi_priorjump(str, ret))
		return (1);
	else if (str[0] == ' ' && ret == 1)
		line_cursor_motion(MRIGHT, g_env.count);
	else if ((str[0] == 'h' || str[0] == 127) && ret == 1)
		line_cursor_motion(MLEFT, g_env.count);
	else if (str[0] == 'l' && ret == 1)
		line_cursor_motion(MRIGHT, g_env.count);
	else if ((str[0] == 'w' || str[0] == 'W') && ret == 1)
		line_rjump();
	else if ((str[0] == 'e' || str[0] == 'E') && ret == 1)
		vi_ejump(g_env.count);
	else if ((str[0] == 'b' || str[0] == 'B') && ret == 1)
		line_ljump();
	else
		return (vi_spec_motion(str, ret));
	if (g_env.mode->v_del)
		vi_cdel();
	if (g_env.mode->v_yank)
		vi_cpy();
	vi_reset_count(str);
	return (1);
}
