/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_resetcurs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:22:35 by roliveir          #+#    #+#             */
/*   Updated: 2019/06/11 17:30:35 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"
#include <term.h>

static int			line_len(int pos)
{
	int				len;

	len = 0;
	while (line_getx(pos))
	{
		pos--;
		len++;
	}
	return (len);
}

static void			line_back_left(int pos)
{
	int				i;
	int				len_line;

	while (pos > g_env.cm->pos)
	{
		i = -1;
		if (!line_getx(pos))
		{
			len_line = line_len(pos - 1);
			tputs(g_env.tc->up, 1, ft_putchar);
			if (pos - len_line > g_env.cm->pos)
				pos -= len_line;
			else
			{
				if (++i < len_line)
				{
					tputs(tparm(g_env.tc->ri, len_line - i), 1, ft_putchar);
					i += len_line - i;
				}
			}
		}
		else
			tputs(g_env.tc->le, 1, ft_putchar);
		pos--;
	}
}

static void			line_reset_autocomp(void)
{
	int				ll;

	if (!g_data.lw || g_data.y >= g_env.cm->term_y)
		return ;
	if (g_data.x + 2 > 0)
		tputs(tparm(g_env.tc->lem, g_data.x + 1), 1, ft_putchar);
	if (g_data.y > 0)
		tputs(tparm(g_env.tc->upm, g_data.y), 1, ft_putchar);
	ll = line_len(g_env.len);
	tputs(tparm(g_env.tc->ri, ll), 1, ft_putchar);
}

void				line_reset_cursor(void)
{
	line_reset_autocomp();
	line_back_left(g_env.len);
	if (!line_getx(g_env.cm->pos)
			&& g_env.len % g_env.cm->term_x == 0)
	{
		tputs(g_env.tc->cr, 1, ft_putchar);
		tputs(g_env.tc->doo, 1, ft_putchar);
	}
}
