/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_calclen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 08:38:20 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/28 21:50:33 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

static void		auto_calclstlen(void)
{
	t_lstword	*tmp;

	tmp = g_data.lw;
	while (g_data.lw)
	{
		if (g_data.lw->len > g_data.lenmax)
			g_data.lenmax = g_data.lw->len;
		g_data.lw = g_data.lw->next;
		g_data.lenlst++;
	}
	g_data.lw = tmp;
}

static void		auto_calc_cor(void)
{
	int		k;

	k = g_data.lenlst % g_data.wordpline;
	k = k ? 1 : 0;
	g_data.y = (int)(g_data.lenlst / g_data.wordpline) + k;
	g_data.x = k ? g_data.lenlst % g_data.wordpline : g_data.wordpline;
	g_data.x = g_data.x * (g_data.lenmax + 2);
}

void			auto_calclen(void)
{
	if (!g_data.lw || !g_data.lw->name)
		return ;
	auto_calclstlen();
	if (!(g_data.wordpline = (int)((g_env.cm->term_x - 1)
					/ (g_data.lenmax + 2))))
	{
		g_data.y = g_env.cm->term_y;
		return ;
	}
	auto_calc_cor();
}
