/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_com_motion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 13:20:36 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/26 13:20:00 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

static int			ft_vi_priorjump(char *str, int ret)
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

static int			ft_vi_spec_motion(char *str, int ret)
{
	if (str[0] == '^' && ret == 1)
		ft_home(0);
	else if (str[0] == '$' && ret == 1)
		ft_end();
	else if (str[0] == '0' && ret == 1)
		ft_home(1);
	else if (str[0] == '|' && ret == 1)
		ft_pipejump(g_env.mode->v_count);
	else if (str[0] == ';' && ret == 1)
		ft_repeat();
	else if (str[0] == ',' && ret == 1)
		ft_rev_repeat();
	else
		return (0);
	if (g_env.mode->v_del)
		ft_cdel();
	if (g_env.mode->v_yank)
		ft_vi_cpy();
	ft_reset_count(str);
	return (1);
}

int					ft_vi_motion(char *str, int ret)
{
	if (ft_vi_priorjump(str, ret))
		return (1);
	else if (str[0] == ' ' && ret == 1)
		ft_cursor_motion(MRIGHT, g_env.mode->v_count);
	else if (str[0] == 'h' && ret == 1)
		ft_cursor_motion(MLEFT, g_env.mode->v_count);
	else if (str[0] == 'l' && ret == 1)
		ft_cursor_motion(MRIGHT, g_env.mode->v_count);
	else if ((str[0] == 'w' || str[0] == 'W') && ret == 1)
		ft_wjump(g_env.mode->v_count);
	else if ((str[0] == 'e' || str[0] == 'E') && ret == 1)
		ft_ejump(g_env.mode->v_count);
	else if ((str[0] == 'b' || str[0] == 'B') && ret == 1)
		ft_bjump(g_env.mode->v_count);
	else
		return (ft_vi_spec_motion(str, ret));
	if (g_env.mode->v_del)
		ft_cdel();
	if (g_env.mode->v_yank)
		ft_vi_cpy();
	ft_reset_count(str);
	return (1);
}
