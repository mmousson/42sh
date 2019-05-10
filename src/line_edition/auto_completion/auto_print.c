/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 09:53:19 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/10 11:19:40 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "line_edition.h"
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
	lenroot = (int)ft_strlen(g_data.root);
	line_paste(&(g_data.lw->name[lenroot]), 1);
	if (g_data.lw->type == 4)
		line_paste("/", 1);
	else
		line_paste(" ", 1);
	auto_free();
	return (1);
}

static void			auto_printprint(int tmp)
{
	int				i;

	i = -1;
	auto_print_select();
	auto_print_color();
	ft_putstr(g_data.lw->name);
	tputs(g_env.tc->me, 1, ft_putchar);
	auto_print_select();
	if (g_data.lw->type == 4)
		ft_putchar('/');
	while (tmp > 1 && ++i < g_data.lenmax - g_data.lw->len)
		ft_putchar(' ');
	tputs(g_env.tc->me, 1, ft_putchar);
	while (tmp > 1 && ++i < g_data.lenmax + 3 - g_data.lw->len)
		ft_putchar(' ');
}

int					auto_printaligned(void)
{
	int				wordpline;
	int				tmp_w;
	t_lstword		*tmp;

	tmp = g_data.lw;
	g_data.status = g_data.status ? g_data.status : 1;
	wordpline = (int)(g_env.cm->term_x / (g_data.lenmax + 2));
	tmp_w = wordpline;
	ft_putchar('\n');
	while (g_data.lw)
	{
		auto_printprint(tmp_w);
		tmp_w--;
		if (tmp_w < 1 && g_data.lw->next)
		{
			tmp_w = wordpline;
			ft_putchar('\n');
		}
		g_data.lw = g_data.lw->next;
	}
	g_data.lw = tmp;
	return (0);
}

int					auto_printword(void)
{
	DIR				*dir;
	struct dirent	*dt;

	if (!(dir = opendir(g_data.path)))
		return (1);
	while ((dt = readdir(dir)))
	{
		if (auto_checkroot(dt->d_name, g_data.root))
			auto_lstword(dt->d_name, dt->d_type);
	}
	(void)closedir(dir);
	auto_calclen();
	if (g_data.lenlst < 2)
		return (auto_printcomp());
	return (1);
}
