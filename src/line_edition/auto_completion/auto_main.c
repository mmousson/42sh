/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 16:52:20 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/28 08:43:23 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

int					auto_return(void)
{
	t_lstword		*tmp;

	g_data.status = 0;
	tmp = g_data.lw;
	while (g_data.lw && g_data.type != 3)
	{
		if (g_data.lw->select)
		{
			if (g_data.lw->type != 9 && g_data.lw->type != 14)
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

void				auto_keep_comp(char *str, int ret)
{
	if (g_data.status == 2 && str[0] != '\t' && str[0] != '\n'
			&& !auto_istabshift(str, ret))
	{
		auto_free();
		ft_bzero(&g_data, sizeof(t_autodata));
	}
}

static int			auto_option(int back)
{
	if (g_data.status == 1)
	{
		if (g_data.type == 1)
			auto_compath(back);
		else if (g_data.type == 0 || g_data.type == 2)
			auto_comproot(back);
		else if (g_data.type == 3)
			auto_compoption(back);
	}
	else if (g_data.status == 2)
		return (auto_choose(back));
	else
		return (0);
	return (1);
}

static int			auto_manager(int back)
{
	int			tmp;

	tmp = auto_getype();
	if (g_data.status != 2 && tmp != g_data.type)
		auto_free();
	if (auto_isblank())
		line_paste("    ", g_env.count);
	else if (auto_option(back))
		return (1);
	else
	{
		auto_filldata();
		return (auto_printword());
	}
	return (1);
}

int					auto_completion(char *str, int ret)
{
	if (str[0] == '\t' && ret == 1)
		return (auto_manager(0));
	else if (auto_istabshift(str, ret))
		return (auto_manager(1));
	return (0);
}
