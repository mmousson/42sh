/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 14:12:12 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/25 00:08:58 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "line_edition.h"

void				sh_switch_term(int reset)
{
	if (!g_env.tc->tc)
		return ;
	if ((tcgetattr(g_env.t_fd, &(g_env.term))) == -1)
		sh_errorterm(TBADFD);
	if (reset)
	{
		g_env.term.c_lflag |= (ECHO | ICANON);
		#ifndef __linux__
		g_env.term.c_cc[VDSUSP] = CTRLY;
		#endif
//		sh_reset_signal(1);
	}
	else
	{
//		sh_signal_handler(1);
		g_env.term.c_lflag &= ~(ECHO | ICANON);
		tputs(g_env.tc->key[0], 1, ft_putchar);
		#ifndef __linux__
		g_env.term.c_cc[VDSUSP] = _POSIX_VDISABLE;
		#endif
	}
	if ((tcsetattr(g_env.t_fd, TCSANOW, &(g_env.term))) == -1)
		sh_errorterm(TBADFD);
}

void				sh_errorterm(t_error error)
{
	ft_putstr_fd("42sh: error ID=", STDERR_FILENO);
	ft_putnbr_fd(error, STDERR_FILENO);
	ft_putstr_fd(" Exiting\n", STDERR_FILENO);
	if (error != TBADFD)
	{
		sh_switch_term(1);
		close(g_env.t_fd);
	}
	line_delenv();
	exit(error);
}

int					sh_quiterm(void)
{
	if (g_env.isatty)
	{
		sh_switch_term(1);
		close(g_env.t_fd);
	}
	line_delenv();
	exit(0);
}

static void			sh_initerm(void)
{
	int				ret;
	char			*type;

	type = getenv("TERM");
	if (type && (ret = tgetent(NULL, type)) < 1)
		g_env.tc->tc = 0;
	if ((g_env.t_fd = open(ttyname(STDIN_FILENO), O_RDWR)) < 0)
		sh_errorterm(TTTYNAME);
	if (tcgetattr(g_env.t_fd, &(g_env.term)) == -1)
		sh_errorterm(TBADFD);
	line_update_termsize();
}

void				sh_configterm(void)
{
	if (isatty(STDIN_FILENO))
		g_env.isatty = 1;
	else
		return ;
	sh_initerm();
	if (!caps_addtermcaps(g_env.tc))
		g_env.tc->tc = 0;
	if (!g_env.tc->tc)
		return ;
	g_env.term.c_cc[VMIN] = 1;
	g_env.term.c_cc[VTIME] = 0;
	#ifndef __linux__
	g_env.term.c_cc[VDSUSP] = _POSIX_VDISABLE;
	#endif
	g_env.term.c_lflag &= ~(ICANON | ECHO);
	if ((tcsetattr(g_env.t_fd, TCSANOW, &(g_env.term))) == -1)
		sh_errorterm(TBADFD);
	caps_active_termcaps();
}
