/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 03:17:58 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/11 19:42:19 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

static void			line_dispatcher(int last_pos)
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

static int			line_isdispatch(void)
{
	if (g_env.cm->pos == g_env.cpos
			|| g_env.cm->pos == g_env.mode->v_pos)
		return (1);
	if (!g_env.mode->n_select && !g_env.mode->v_visual)
		return (1);
	return (0);
}

static int			line_get_lastpos(void)
{
	if (g_env.mode->n_select)
		return (g_env.cpos);
	if (g_env.mode->v_visual)
		return (g_env.mode->v_pos);
	return (0);
}

int					line_print(void)
{
	int				ret;

	ret = 1;
	if (line_isdispatch())
		ft_putstr(g_env.line);
	else
		line_dispatcher(line_get_lastpos());
	if (g_env.len % g_env.cm->term_x == 0
			&& g_env.cm->pos % g_env.cm->term_x != 0)
	{
		tputs(g_env.tc->cr, 1, ft_putchar);
		tputs(g_env.tc->doo, 1, ft_putchar);
	}
	if (g_data.lw)
		ret = auto_printaligned();
	if (ret == -1)
		ft_putstr("\n42sh: cannot print");
	return (ret);
}
