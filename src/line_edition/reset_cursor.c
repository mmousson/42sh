/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_cursor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:22:35 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/25 09:44:40 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

static int			ft_lenline(int pos)
{
	int				len;

	len = 0;
	while (ft_getx(pos))
	{
		pos--;
		len++;
	}
	return (len);
}

static void			ft_back_left(int pos)
{
	int				i;
	int				len_line;

	while (pos != g_env.cm->pos)
	{
		i = -1;
		if (!ft_getx(pos))
		{
			len_line = ft_lenline(pos - 1);
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

void				ft_reset_cursor(void)
{
	ft_back_left(g_env.len);
	if (!ft_getx(g_env.cm->pos)
			&& g_env.len % g_env.cm->term_x == 0)
	{
		tputs(g_env.tc->cr, 1, ft_putchar);
		tputs(g_env.tc->doo, 1, ft_putchar);
	}
}
