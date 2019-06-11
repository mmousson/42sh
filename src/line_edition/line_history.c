/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 23:07:53 by roliveir          #+#    #+#             */
/*   Updated: 2019/06/11 13:28:38 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

static int				line_is_uhistory(int count)
{
	int					lstlen;
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

static int				line_is_dhistory(int count)
{
	if (count > g_env.index)
		return (0);
	return (1);
}

void					line_get_uhistory(int count)
{
	int					i;
	t_history			*tmp;
	char				buff[BUFF_SIZE + 1];

	i = -1;
	tmp = g_env.ry;
	if (!line_is_uhistory(count))
		return ;
	ft_strcpy(buff, g_env.line);
	while (g_env.ry && ++i < g_env.index)
		g_env.ry = g_env.ry->next;
	if (!g_env.ry)
	{
		g_env.ry = tmp;
		return ;
	}
	g_env.index += count;
	if (!(g_env.line = line_alloc_history(0)))
		sh_errorterm(TMALLOC);
	g_env.ry = tmp;
	line_cursor_ry();
	if (!ft_strcmp(buff, g_env.line))
		line_get_uhistory(count);
}

void					line_get_dhistory(int count)
{
	int					i;
	t_history			*tmp;
	char				buff[BUFF_SIZE + 1];

	i = -1;
	if (!g_env.index || !line_is_dhistory(count))
		return ;
	ft_strcpy(buff, g_env.line);
	if (!(g_env.index -= count))
		g_env.line = line_alloc_history(1);
	else
	{
		tmp = g_env.ry;
		while (g_env.ry->next && ++i < g_env.index)
			g_env.ry = g_env.ry->next;
		g_env.ry = g_env.ry->prev;
		if (!(g_env.line = line_alloc_history(0)))
			sh_errorterm(TMALLOC);
		g_env.ry = tmp;
	}
	if (!g_env.line)
		sh_errorterm(TMALLOC);
	line_cursor_ry();
	if (!ft_strcmp(buff, g_env.line))
		line_get_dhistory(count);
}

void					line_reset_history(void)
{
	while (g_env.ry && g_env.ry->prev)
		g_env.ry = g_env.ry->prev;
	g_env.index = 0;
}
