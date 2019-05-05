/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_cxjump.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 10:05:32 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/05 16:40:44 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

static void			line_newcx(void)
{
	if (!(g_env.cx = (t_ctrlxx*)ft_memalloc(sizeof(t_ctrlxx))))
		sh_errorterm(TMALLOC);
	g_env.cx->pmax = g_env.len;
	g_env.cx->pmin = g_env.p_size;
	g_env.cx->count_x = 0;
	g_env.cx->lastp = 1;
}

static void			line_cxend(void)
{
	int				k;

	k = 1;
	g_env.cx->lastp = 1;
	if (g_env.cm->pos > g_env.cx->pmax)
		k = 0;
	g_env.cx->pmin = g_env.cm->pos;
	line_cursor_motion(MLEFT + k, ft_abs(g_env.cx->pmax - g_env.cm->pos));
	if (!k)
	{
		k = g_env.cx->pmax;
		g_env.cx->pmax = g_env.cx->pmin;
		g_env.cx->pmin = k;
		g_env.cx->lastp = g_env.cx->lastp ? 0 : 1;
	}
}

static void			line_cxstart(void)
{
	int				k;

	k = 1;
	g_env.cx->lastp = 0;
	if (g_env.cm->pos < g_env.cx->pmin)
		k = 0;
	g_env.cx->pmax = g_env.cm->pos;
	line_cursor_motion(MRIGHT - k, ft_abs(g_env.cm->pos - g_env.cx->pmin));
	if (!k)
	{
		k = g_env.cx->pmin;
		g_env.cx->pmin = g_env.cx->pmax;
		g_env.cx->pmax = k;
		g_env.cx->lastp = g_env.cx->lastp ? 0 : 1;
	}
}

void				line_cxjump(void)
{
	if (!g_env.cx)
		line_newcx();
	g_env.cx->count_x++;
	if (g_env.cx->count_x == 1)
		return ;
	if (!g_env.cx->lastp)
		line_cxend();
	else
		line_cxstart();
	g_env.cx->count_x = 0;
}
