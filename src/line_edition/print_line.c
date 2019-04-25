/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 03:17:58 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/25 09:44:48 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

static void			ft_dispatcher(int last_pos)
{
	int				i;

	i = 0;
	while (i < g_env.cm->pos && i < last_pos)
	{
		ft_putchar(g_env.line[i]);
		i++;
	}
	tputs(g_env.tc->mr, 1, ft_putchar);
	while (i < g_env.cm->pos || i < last_pos)
	{
		ft_putchar(g_env.line[i]);
		i++;
	}
	tputs(g_env.tc->me, 1, ft_putchar);
	if (g_env.line[i])
		ft_putstr(&(g_env.line[i]));
}

static int			ft_isdispatch(void)
{
	if (g_env.cm->pos == g_env.cpy->pos
			|| g_env.cm->pos == g_env.mode->v_pos)
		return (1);
	if (!g_env.mode->n_select && !g_env.mode->v_visual)
		return (1);
	return (0);
}

static int			ft_get_lastpos(void)
{
	if (g_env.mode->n_select)
		return (g_env.cpy->pos);
	if (g_env.mode->v_visual)
		return (g_env.mode->v_pos);
	return (0);
}

void				ft_print_line(void)
{
	if (ft_isdispatch())
		ft_putstr(g_env.line);
	else
		ft_dispatcher(ft_get_lastpos());
	if (g_env.len % g_env.cm->term_x == 0
			&& g_env.cm->pos % g_env.cm->term_x != 0)
	{
		tputs(g_env.tc->cr, 1, ft_putchar);
		tputs(g_env.tc->doo, 1, ft_putchar);
	}
}
