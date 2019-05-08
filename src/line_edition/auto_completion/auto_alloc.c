/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 12:31:57 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/07 10:07:46 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

char				*auto_getpath(void)
{
	char			*path;
	int				i;
	int				si;

	i = g_env.cm->pos - 1;
	while (i - g_env.p_size + 1 && !auto_newtoken(g_env.line[i]))
		i--;
	si = i;
	i = g_env.cm->pos - 1;
	while (i > si && !auto_ispathcarac(g_env.line[i]))
		i--;
	if (si == g_env.cm->pos - 1)
		path = ft_strdup("./");
	else if (i == si)
		path = ft_strsub(g_env.line, i, g_env.cm->pos - 1);
	else
		path = ft_strsub(g_env.line, si + 1, i);
	if (!path)
		sh_errorterm(TMALLOC);
	return (path);
}

char				*auto_getroot(void)
{
	char			*root;
	int				i;

	i = g_env.cm->pos - 1;
	while (i - g_env.p_size + 1
			&& !auto_newtoken(g_env.line[i])
			&& !auto_ispathcarac(g_env.line[i]))
		i--;
	if (!(root = ft_strsub(g_env.line, i + 1, g_env.cm->pos - 1)))
		sh_errorterm(TMALLOC);
	return (root);
}
