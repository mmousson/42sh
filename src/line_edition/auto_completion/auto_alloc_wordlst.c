/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_alloc_wordlst.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 10:07:58 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/29 15:05:32 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

t_lstword		*auto_new_lstword(void)
{
	t_lstword	*lstword;

	if (!(lstword = (t_lstword*)ft_memalloc(sizeof(t_lstword))))
		sh_errorterm(TMALLOC);
	return (lstword);
}

static void		auto_lstword_quit(t_lstword **tmp, char **name)
{
	g_data.lw = *tmp;
	ft_strdel(name);
	sh_errorterm(TMALLOC);
}

static void		auto_add_lstword(char *orignal, char **name, int index)
{
	t_lstword	*tmp;

	tmp = g_data.lw;
	if (auto_check_double(*name))
		return ;
	if (!(g_data.lw->next = (t_lstword*)ft_memalloc(sizeof(t_lstword))))
		auto_lstword_quit(&tmp, name);
	if (!(g_data.lw->next->name = (t_name*)ft_memalloc(sizeof(t_name))))
		auto_lstword_quit(&tmp, name);
	g_data.lw->next->name->name = auto_alloc_name(name);
	g_data.lw->next->len = (int)ft_strlen(g_data.lw->next->name->name);
	g_data.lw->next->type = auto_getstatype(orignal,
			&g_data.lw->next->carac, index);
	if (g_data.lw->next->type != 7)
		g_data.lw->next->len++;
	g_data.lw = tmp;
}

void			auto_lstword(char *orignal, char **name, int index)
{
	if (!g_data.lw)
		return ;
	if (!g_data.lw->name)
	{
		if (!(g_data.lw->name = (t_name*)ft_memalloc(sizeof(t_name))))
			auto_lstword_quit(&g_data.lw, name);
		g_data.lw->name->name = auto_alloc_name(name);
		g_data.lw->len = (int)ft_strlen(g_data.lw->name->name);
		g_data.lw->type = auto_getstatype(orignal,
				&g_data.lw->carac, 0);
		if (g_data.lw->type != 7)
			g_data.lw->len++;
	}
	else
	{
		if (!g_data.lw->next && !ft_strcmp(g_data.lw->name->name, *name))
			return ;
		auto_add_lstword(orignal, name, index);
	}
}

void			auto_lstmanager(struct dirent *dt, int i)
{
	char		*name;

	if (!(name = ft_strdup(dt->d_name)))
		sh_errorterm(TMALLOC);
	if (auto_checkroot(dt->d_name, g_data.root))
		auto_lstword(dt->d_name, &name, i);
	ft_strdel(&name);
}
