/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_choose.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 10:31:11 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/10 11:19:42 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

static void		auto_replace(char *str, int type)
{
	int			size;

	size = g_env.cm->pos - g_data.spos;
	if (size)
	{
		g_env.line = line_delchar(size);
		line_cursor_motion(MLEFT, size);
	}
	line_paste(str, 1);
	if (type == 4)
		line_paste("/", 1);
}

int				auto_return(void)
{
	t_lstword	*tmp;

	g_data.status = 0;
	tmp = g_data.lw;
	while (g_data.lw)
	{
		if (g_data.lw->select)
		{
			auto_replace(g_data.lw->name, g_data.lw->type);
			if (g_data.lw->type != 4)
				line_paste(" ", 1);
			g_data.lw = tmp;
			auto_free();
			return (1);
		}
		g_data.lw = g_data.lw->next;
	}
	g_data.lw = tmp;
	auto_free();
	return (1);
}

int				auto_choose(void)
{
	t_lstword	*tmp;

	tmp = g_data.lw;
	g_data.status = 2;
	while (g_data.lw->next)
	{
		if (g_data.lw->select)
		{
			g_data.lw->select = 0;
			g_data.lw->next->select = 1;
			auto_replace(g_data.lw->next->name, g_data.lw->next->type);
			g_data.lw = tmp;
			return (1);
		}
		g_data.lw = g_data.lw->next;
	}
	if (g_data.lw->select)
		g_data.lw->select = 0;
	g_data.lw = tmp;
	g_data.lw->select = 1;
	auto_replace(g_data.lw->name, g_data.lw->type);
	return (1);
}
