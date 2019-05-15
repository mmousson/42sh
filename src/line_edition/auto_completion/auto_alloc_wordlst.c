/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_alloc_wordlst.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 10:07:58 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/15 12:16:17 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

static void		auto_free_lstword(t_lstword *lw)
{
	if (!lw)
		return ;
	if (lw->next)
		auto_free_lstword(lw->next);
	if (lw->name)
		ft_strdel(&(lw->name));
	ft_memdel((void**)&lw);
}

void			auto_free(void)
{
	auto_free_lstword(g_data.lw);
	ft_del_words_tables(&(g_data.path));
	ft_strdel(&g_data.root);
	ft_bzero(&g_data, sizeof(t_autodata));
	g_data.lw = NULL;
}

t_lstword		*auto_new_lstword(void)
{
	t_lstword	*lstword;

	if (!(lstword = (t_lstword*)ft_memalloc(sizeof(t_lstword))))
		sh_errorterm(TMALLOC);
	return (lstword);
}

static void		auto_add_lstword(char *name, int index)
{
	t_lstword	*tmp;

	tmp = g_data.lw;
	while (g_data.lw->next)
	{
		if (!ft_strcmp(g_data.lw->name, name))
		{
			g_data.lw = tmp;
			return ;
		}
		g_data.lw = g_data.lw->next;
	}
	if (!(g_data.lw->next = (t_lstword*)ft_memalloc(sizeof(t_lstword))))
	{
		g_data.lw = tmp;
		auto_free_lstword(g_data.lw);
		sh_errorterm(TMALLOC);
	}
	if (!(g_data.lw->next->name = ft_strdup(name)))
	{
		g_data.lw = tmp;
		auto_free_lstword(g_data.lw);
		sh_errorterm(TMALLOC);
	}
	g_data.lw->next->len = (int)ft_strlen(g_data.lw->next->name);
	g_data.lw->next->type = auto_getstatype(g_data.lw->next->name,
			&g_data.lw->next->carac, index);
	if (g_data.lw->next->type != 7 && g_data.lw->type != 14)
		g_data.lw->next->len++;
	g_data.lw = tmp;
}

void			auto_lstword(char *name, int index)
{
	if (!g_data.lw)
		return ;
	if (!g_data.lw->name)
	{
		if (!(g_data.lw->name = ft_strdup(name)))
		{
			auto_free_lstword(g_data.lw);
			sh_errorterm(TMALLOC);
		}
		g_data.lw->len = (int)ft_strlen(g_data.lw->name);
		g_data.lw->type = auto_getstatype(g_data.lw->name,
				&g_data.lw->carac, 0);
		if (g_data.lw->type != 7 && g_data.lw->type != 14)
			g_data.lw->len++;
	}
	else
	{
		if (!g_data.lw->next && !ft_strcmp(g_data.lw->name, name))
			return ;
		auto_add_lstword(name, index);
	}
}
