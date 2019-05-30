/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_termcaps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 21:44:36 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/30 18:30:28 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"
#include <term.h>

void			auto_print_select(void)
{
	if (g_data.lw->select)
		tputs(g_env.tc->mr, 1, ft_putchar);
}

void			auto_print_color(void)
{
	if (!g_data.lw->select)
		tputs(tparm(g_env.tc->af, g_data.lw->type), 1, ft_putchar);
}
