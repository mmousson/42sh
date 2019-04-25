/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 23:07:53 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/25 10:46:40 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

static int				ft_is_uhistory(int count)
{
	int				lstlen;
	t_history			*tmp;

	lstlen = 0;
	tmp = g_env.ry;
	while (g_env.ry)
	{
		lstlen++;
		g_env.ry = g_env.ry->next;
	}
	g_env.ry = tmp;
	if (count + g_env.index > lstlen)
		return (0);
	return (1);
}

static int				ft_is_dhistory(int count)
{
	if (count > g_env.index)
		return (0);
	return (1);
}

void					ft_get_uhistory(int count)
{
	int					i;
	t_history			*tmp;

	i = -1;
	tmp = g_env.ry;
	if (!ft_is_uhistory(count))
		return ;
	while (g_env.ry && ++i < g_env.index)
		g_env.ry = g_env.ry->next;
	if (!g_env.ry)
	{
		g_env.ry = tmp;
		return ;
	}
	g_env.index += count;
	if (!(g_env.line = ft_alloc_history(0)))
		ft_errorterm(TMALLOC);
	g_env.ry = tmp;
	ft_cursor_ry();
}

void					ft_get_dhistory(int count)
{
	int					i;
	t_history			*tmp;

	i = -1;
	if (!g_env.index || !ft_is_dhistory(count))
		return ;
	g_env.index -= count;
	if (!g_env.index)
		g_env.line = ft_alloc_history(1);
	else
	{
		tmp = g_env.ry;
		while (g_env.ry->next && ++i < g_env.index)
			g_env.ry = g_env.ry->next;
		g_env.ry = g_env.ry->prev;
		if (!(g_env.line = ft_alloc_history(0)))
			ft_errorterm(TMALLOC);
		g_env.ry = tmp;
	}
	if (!g_env.line)
		ft_errorterm(TMALLOC);
	ft_cursor_ry();
}

void					ft_reset_history(void)
{
	while (g_env.ry && g_env.ry->prev)
		g_env.ry = g_env.ry->prev;
	g_env.index = 0;
}
