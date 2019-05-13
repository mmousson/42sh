/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 12:31:57 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/13 09:39:13 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

char				*auto_getpath(void)
{
	int				i;
	int				si;
	char			*path;

	i = g_env.cm->pos - 1;
	while (i - g_env.p_size + 1 && !auto_newtoken(g_env.line[i]))
		i--;
	si = i;
	i = g_env.cm->pos - 1;
	while (i > si && !auto_ispathcarac(g_env.line[i]))
		i--;
	if (si == g_env.cm->pos - 1 || i == si)
		path = ft_strdup("./");
	else if (si + 1 == i)
		path = ft_strdup("/");
	else
		path = ft_strsub(g_env.line, si + 1, i - si);
	if (!path)
		sh_errorterm(TMALLOC);
	return (path);
}

char				*auto_getroot(void)
{
	int				i;
	char			*root;

	i = g_env.cm->pos - 1;
	while (i - g_env.p_size + 1
			&& !auto_newtoken(g_env.line[i])
			&& !auto_ispathcarac(g_env.line[i]))
		i--;
	if (!(root = ft_strsub(g_env.line, i + 1, g_env.cm->pos - 1)))
		sh_errorterm(TMALLOC);
	return (root);
}

void				auto_filldata(void)
{
	char			*path;

	path = NULL;
	g_data.type = auto_getype();
	g_data.root = auto_getroot();
	if (g_data.type == 1)
		path = auto_getpath();
	else if (g_data.type == 0)
		path = getenv("PATH");
	if (!path || !(g_data.path = ft_strsplit(path, ':')))
		return ;
	if (g_data.type)
		ft_strdel(&path);
	g_data.lw = auto_new_lstword();
	g_data.spos = g_env.cm->pos;
}
