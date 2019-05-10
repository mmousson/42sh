/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 12:31:57 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/10 10:37:27 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

static void			auto_getpath(void)
{
	int				i;
	int				si;

	i = g_env.cm->pos - 1;
	while (i - g_env.p_size + 1 && !auto_newtoken(g_env.line[i]))
		i--;
	si = i;
	i = g_env.cm->pos - 1;
	while (i > si && !auto_ispathcarac(g_env.line[i]))
		i--;
	if (si == g_env.cm->pos - 1 || i == si)
		g_data.path = ft_strdup("./");
	else
		g_data.path = ft_strsub(g_env.line, si + 1, i);
	if (!g_data.path)
		sh_errorterm(TMALLOC);
}

static void			auto_getroot(void)
{
	int				i;

	i = g_env.cm->pos - 1;
	while (i - g_env.p_size + 1
			&& !auto_newtoken(g_env.line[i])
			&& !auto_ispathcarac(g_env.line[i]))
		i--;
	if (!(g_data.root = ft_strsub(g_env.line, i + 1, g_env.cm->pos - 1)))
		sh_errorterm(TMALLOC);
}

void				auto_filldata(void)
{
	g_data.type = auto_getype();
	auto_getroot();
	if (g_data.type == 1)
	{
		auto_getpath();
		g_data.lw = auto_new_lstword();
	}
	g_data.spos = g_env.cm->pos;
}
