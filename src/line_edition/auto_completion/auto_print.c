/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 09:53:19 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/25 18:57:22 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "line_edition.h"
#include "sh42.h"
#include <term.h>

static int			auto_printcomp(void)
{
	int				lenroot;

	g_data.status = 0;
	if (!g_data.lenlst)
	{
		auto_free();
		return (1);
	}
	lenroot = auto_lenrootwbs();
	line_paste(&(g_data.lw->name[lenroot]), 1);
	if (g_data.lw->type == 9 || g_data.lw->type == 14)
		line_paste("/", 1);
	else
		line_paste(" ", 1);
	auto_free();
	return (1);
}

static void			auto_printprint(void)
{
	int				i;

	i = -1;
	auto_print_select();
	auto_print_color();
	ft_putstr(g_data.lw->name);
	tputs(g_env.tc->me, 1, ft_putchar);
	auto_print_select();
	if (g_data.lw->type != 7)
		ft_putchar(g_data.lw->carac);
	while (++i < g_data.lenmax - g_data.lw->len)
		ft_putchar(' ');
	tputs(g_env.tc->me, 1, ft_putchar);
	while (++i < g_data.lenmax + 3 - g_data.lw->len)
		ft_putchar(' ');
}

int					auto_printaligned(void)
{
	int				tmp_w;
	t_lstword		*tmp;

	if (g_data.y >= g_env.cm->term_y)
	{
		auto_free();
		return (-1);
	}
	tmp = g_data.lw;
	g_data.status = g_data.status ? g_data.status : 1;
	tmp_w = g_data.wordpline;
	ft_putchar('\n');
	while (g_data.lw)
	{
		auto_printprint();
		tmp_w--;
		if (tmp_w < 1 && g_data.lw->next)
		{
			tmp_w = g_data.wordpline;
			ft_putchar('\n');
		}
		g_data.lw = g_data.lw->next;
	}
	g_data.lw = tmp;
	return (1);
}

static void			auto_printbuilt(void)
{
	int				i;

	i = 0;
	auto_printvar();
	if (g_data.type)
		return ;
	while (g_builtins[i].name)
	{
		if (auto_checkroot(g_builtins[i].name, g_data.root))
			auto_lstword(g_builtins[i].name, &(g_builtins[i].name), 0);
		i++;
	}
}

int					auto_printword(void)
{
	DIR				*dir;
	struct dirent	*dt;
	int				i;
	char			*name;

	i = -1;
	while (g_data.type != 2 && g_data.path[++i])
	{
		if (!(dir = opendir(g_data.path[i])))
			break ;
		while ((dt = readdir(dir)))
		{
			if (!(name = ft_strdup(dt->d_name)))
				sh_errorterm(TMALLOC);
			if (auto_checkroot(dt->d_name, g_data.root))
				auto_lstword(dt->d_name, &name, i);
		}
		(void)closedir(dir);
	}
	auto_printbuilt();
	auto_sort();
	auto_calclen();
	if (g_data.lenlst < 2)
		return (auto_printcomp());
	return (1);
}
