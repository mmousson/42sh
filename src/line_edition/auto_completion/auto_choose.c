/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_choose.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 10:31:11 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/28 08:39:37 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

static void			auto_choose_select(int back)
{
	g_data.lw->select = back;
	g_data.lw->next->select = back ? 0 : 1;
	if (!back)
		auto_replace(g_data.lw->next->name->name, g_data.lw->next->type);
	else
		auto_replace(g_data.lw->name->name, g_data.lw->type);
}

static void			auto_choose_back(int back)
{
	t_lstword		*tmp;

	tmp = g_data.lw;
	while (g_data.lw->next)
	{
		if (g_data.lw->next->select)
		{
			auto_choose_select(back);
			g_data.lw = tmp;
			return ;
		}
		g_data.lw = g_data.lw->next;
	}
	tmp->select = 0;
	g_data.lw->select = 1;
	auto_replace(g_data.lw->name->name, g_data.lw->type);
	g_data.lw = tmp;
}

static void			auto_choose_front(int back)
{
	t_lstword		*tmp;

	tmp = g_data.lw;
	while (g_data.lw->next)
	{
		if (g_data.lw->select)
		{
			auto_choose_select(back);
			g_data.lw = tmp;
			return ;
		}
		g_data.lw = g_data.lw->next;
	}
	g_data.lw->select = 0;
	g_data.lw = tmp;
	g_data.lw->select = 1;
	auto_replace(g_data.lw->name->name, g_data.lw->type);
}

int					auto_choose(int back)
{
	g_data.status = 2;
	if (back)
		auto_choose_back(back);
	else
		auto_choose_front(back);
	return (1);
}
