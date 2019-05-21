/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 13:53:55 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/21 18:20:11 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>

void				sig_sigint(void)
{
	g_env.sigc = 1;
	g_env.search = 0;
	g_env.h_len = 0;
	ft_strdel(&g_env.h_word);
	line_end();
	ft_putchar('\n');
	ioctl(0, TIOCSTI, "^D");
}

void				sig_sigwinch(void)
{
	line_update_termsize();
	auto_calclen();
	line_clear();
	line_print();
	line_reset_cursor();
}
