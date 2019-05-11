/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_resetcurs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:22:35 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/11 19:42:21 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

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

	while (pos != g_env.cm->pos)
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
				while (++i < len_line)
					tputs(g_env.tc->nd, 1, ft_putchar);
			}
		}
		else
			tputs(g_env.tc->le, 1, ft_putchar);
		pos--;
	}
}

static void			line_reset_autocomp(int ret_p)
{
	int				x;
	int				y;
	int				ll;
	int				tmp;

	tmp = -1;
	if (ret_p == -1)
	{
		while (++tmp < 18)
			tputs(g_env.tc->le, 1, ft_putchar);
		tputs(g_env.tc->up, 1, ft_putchar);
	}
	else
	{
		if (!g_data.lw)
			return ;
		x = g_data.x;
		y = g_data.y;
		while (--x + 1)
			tputs(g_env.tc->le, 1, ft_putchar);
		while (--y + 1)
			tputs(g_env.tc->up, 1, ft_putchar);
	}
	ll = line_len(g_env.len);
	x = -1;
	while (++x < ll)
		tputs(g_env.tc->nd, 1, ft_putchar);

}

void				line_reset_cursor(int ret_p)
{
	line_reset_autocomp(ret_p);
	line_back_left(g_env.len);
	if (!line_getx(g_env.cm->pos)
			&& g_env.len % g_env.cm->term_x == 0)
	{
		tputs(g_env.tc->cr, 1, ft_putchar);
		tputs(g_env.tc->doo, 1, ft_putchar);
	}
}
