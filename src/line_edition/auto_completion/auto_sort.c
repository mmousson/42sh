/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 08:44:58 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/28 09:01:11 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

static t_lstword		*auto_findmin(t_lstword *lw)
{
	t_lstword			*min;

	min = lw;
	while (lw && lw->next)
	{
		if (ft_strcmp(lw->name->name, min->name->name) < 0)
			min = lw;
		lw = lw->next;
	}
	return (min);
}

void					auto_sort(void)
{
	t_lstword			*tmp;
	t_lstword			*min;

	tmp = g_data.lw;
	if (!g_data.lw || !g_data.lw->next || g_data.type == 3)
		return ;
	while (g_data.lw->next)
	{
		min = auto_findmin(g_data.lw);
		auto_swapstr(&g_data.lw->name->name, &min->name->name);
		auto_swapint(&g_data.lw->type, &min->type);
		auto_swapint(&g_data.lw->len, &min->len);
		auto_swapint(&g_data.lw->select, &min->select);
		auto_swapchar(&g_data.lw->carac, &min->carac);
		g_data.lw = g_data.lw->next;
	}
	g_data.lw = tmp;
}
