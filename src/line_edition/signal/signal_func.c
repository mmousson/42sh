/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 13:53:55 by roliveir          #+#    #+#             */
/*   Updated: 2019/06/16 14:29:55 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"
#include <sys/ioctl.h>

void				sig_sigint(void)
{
	g_env.sigc = 1;
	g_env.search = 0;
	g_env.h_len = 0;
	g_env.mode->n_select = 0;
	auto_free();
	ft_strdel(&g_env.h_word);
	line_end();
	ft_putchar('\n');
	ioctl(0, TIOCSTI, "^D");
}

void				sig_sigwinch(void)
{
	line_update_termsize();
	g_env.cm->tmpy = line_gety(g_env.cm->pos);
	auto_free();
	line_clear();
	line_print();
	line_reset_cursor();
}
