/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 02:36:49 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/26 11:36:59 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

void				ft_init_cpy(void)
{
	g_env.mode->n_select = 1;
	g_env.cpy->pos = g_env.cm->pos;
}

static void			ft_escap_cpy(int move_cursor)
{
	g_env.mode->n_select = 0;
	if (!move_cursor || g_env.cm->pos == g_env.cpy->pos)
		return ;
	if (g_env.cm->pos < g_env.cpy->pos)
		ft_cursor_motion(MRIGHT, g_env.cpy->pos - g_env.cm->pos);
	else
		ft_cursor_motion(MLEFT, g_env.cm->pos - g_env.cpy->pos);
}

static void			ft_cpy(int ctrlc)
{
	char			*cpy;
	int				min;
	int				max;

	if (g_env.cm->pos == g_env.cpy->pos)
		return ;
	min = g_env.cpy->pos > g_env.cm->pos ? g_env.cm->pos : g_env.cpy->pos;
	max = min == g_env.cm->pos ? g_env.cpy->pos : g_env.cm->pos;
	if (!(cpy = ft_strsub(g_env.line, min, max - min)))
		ft_errorterm(TMALLOC);
	ft_strdel(&(g_env.cpy->str));
	g_env.cpy->str = cpy;
	if (ctrlc)
		ft_escap_cpy(1);
}

static void			ft_cut(void)
{
	if (g_env.cm->pos == g_env.cpy->pos)
		return ;
	ft_cpy(0);
	if (g_env.cpy->pos < g_env.cm->pos)
	{
		g_env.line = ft_delchar(g_env.cm->pos - g_env.cpy->pos);
		ft_cursor_motion(MLEFT, g_env.cpy->pos - g_env.cm->pos);
		ft_escap_cpy(1);
	}
	else
	{
		g_env.line = ft_delchar_bs(g_env.cpy->pos - g_env.cm->pos);
		ft_cursor_motion(MLEFT, g_env.cm->pos - g_env.cpy->pos);
		ft_escap_cpy(0);
	}
}

int					ft_line_cpy(char *str, int ret)
{
	if (str[0] == 27 && ret == 1)
		ft_escap_cpy(1);
	else if (ft_isaltc(str, ret))
		ft_cpy(1);
	else if (ft_isaltx(str, ret))
		ft_cut();
	ft_line_arrow(str, ret);
	return (1);
}
