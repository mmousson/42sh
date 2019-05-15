/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 11:54:13 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/15 16:28:08 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

int				auto_isblank(void)
{
	int			i;

	i = g_env.p_size;
	while (g_env.line[i] && (g_env.line[i] == ' ' || g_env.line[i] == '\t'))
		i++;
	if (!g_env.line[i])
		return (1);
	return (0);
}

int				auto_checkroot(char *name, char *root)
{
	int			len;

	len = (int)ft_strlen(root);
	if (!len && name[0] == '.')
		return (0);
	if (ft_strncmp(name, root, len))
		return (0);
	return (1);
}

void				auto_calclen(void)
{
	t_lstword		*tmp;
	int				k;

	if (!g_data.lw->name)
		return ;
	tmp = g_data.lw;
	while (g_data.lw)
	{
		if (g_data.lw->len > g_data.lenmax)
			g_data.lenmax = g_data.lw->len;
		g_data.lw = g_data.lw->next;
		g_data.lenlst++;
	}
	g_data.lw = tmp;
	if (!(g_data.wordpline = (int)(g_env.cm->term_x / (g_data.lenmax + 2))))
	{
		g_data.y = g_env.cm->term_y;
		return ;
	}
	k = g_data.lenlst % g_data.wordpline;
	k = k ? 1 : 0;
	g_data.y = (int)(g_data.lenlst / g_data.wordpline) + k;
	g_data.x = k ? g_data.lenlst % g_data.wordpline : g_data.wordpline;
	g_data.x = g_data.x * (g_data.lenmax + 2);
	return ;
}

void				auto_sort(void)
{
	t_lstword		*tmp;

	tmp = g_data.lw;
	if (!g_data.lw || !g_data.lw->next)
		return ;
	while (g_data.lw->next)
	{
		if (ft_strcmp(g_data.lw->name, g_data.lw->next->name) > 0)
		{
			auto_swapstr(&g_data.lw->name, &g_data.lw->next->name);
			auto_swapint(&g_data.lw->type, &g_data.lw->next->type);
			auto_swapint(&g_data.lw->len, &g_data.lw->next->len);
			auto_swapint(&g_data.lw->select, &g_data.lw->next->select);
			auto_swapchar(&g_data.lw->carac, &g_data.lw->next->carac);
			g_data.lw = tmp;
		}
		g_data.lw = g_data.lw->next;
	}
	g_data.lw = tmp;
}
