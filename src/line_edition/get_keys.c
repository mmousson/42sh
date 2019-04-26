/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 03:46:52 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/26 11:37:02 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

static int			ft_cpy_pst(char *str, int ret)
{
	if (ft_isaltc(str, ret) && !g_env.mode->n_select)
		ft_init_cpy();
	else if (ft_isaltv(str, ret) && !g_env.mode->n_select)
		ft_paste(g_env.cpy->str, 1);
	else
		return (0);
	return (1);
}

int					ft_line_history(char *str)
{
	if (!ft_strcmp(g_env.tc->key[MUP], str))
		ft_cursor_motion(MUP, 1);
	else if (!ft_strcmp(g_env.tc->key[MDOWN], str))
		ft_cursor_motion(MDOWN, 1);
	else
		return (0);
	return (1);
}

int					ft_line_arrow(char *str, int ret)
{	
	if (ft_rd_left(str, ret))
		ft_cursor_motion(MLEFT, 1);
	else if (ft_rd_right(str, ret))
		ft_cursor_motion(MRIGHT, 1);
	else if (g_env.mode->mode[MNORMAL] && ft_isaltf(str, ret))
		ft_rjump();
	else if (g_env.mode->mode[MNORMAL] && ft_isaltb(str, ret))
		ft_ljump();
	else if (g_env.mode->mode[MNORMAL] && !ft_strcmp(str, UJUMP))
		ft_cursor_motion(MLEFT, g_env.cm->term_x);
	else if (g_env.mode->mode[MNORMAL] && !ft_strcmp(str, DJUMP))
		ft_cursor_motion(MRIGHT, g_env.cm->term_x);
	else if (g_env.mode->mode[MNORMAL] && !ft_strcmp(g_env.tc->kh, str))
		ft_home(1);
	else if (g_env.mode->mode[MNORMAL] && !ft_strcmp(TEND, str))
		ft_end();
	else
		return (0);
	return (1);
}

int					ft_line_ascii(char *str, int ret)
{
	if (str[0] <= 126 && str[0] >= 32)
		ft_paste(str, 1);
	else if (str[0] == 127 && ret == 1)
	{
		g_env.line = ft_delchar(1);
		g_env.del = 1;
		ft_cursor_motion(MLEFT, 1);
		g_env.del = 0;
	}
	else if (g_env.mode->mode[MNORMAL] && !ft_strcmp(g_env.tc->kd, str))
		g_env.line = ft_delchar_bs(1);
	else
		return (0);
	return (1);
}

int					ft_line_manager(char *str, int ret)
{
	if (str[0] == '\n' && ret == 1)
		return (0);
	else if (str[0] == CTRLD && ret == 1 && g_env.len == g_env.p_size + 1)
	{
		g_env.ctrld = 1;
		return (0);
	}
	else if (ft_line_ascii(str, ret))
		return (1);
	else if (ft_line_arrow(str, ret))
		return (1);
	else if (ft_cpy_pst(str, ret))
		return (1);
	else if (ft_line_history(str))
		return (1);
	else if (ft_vi(str))
		return (1);
	return (1);
}
