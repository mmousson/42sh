/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 14:12:12 by roliveir          #+#    #+#             */
/*   Updated: 2019/06/11 15:08:08 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "line_edition.h"

#ifndef __linux__

static void		set_term_vdsusp(int val)
{
	g_env.term.c_cc[VDSUSP] = val;
}

#else

static void		set_term_vdsusp(int val)
{
	if (val)
		;
}

#endif

void			sh_switch_term(int reset)
{
	if (!g_env.tc->tc)
		return ;
	if ((tcgetattr(g_env.t_fd, &(g_env.term))) == -1)
		sh_errorterm(TBADFD);
	if (reset)
	{
		g_env.term.c_lflag |= (ECHO | ICANON);
		set_term_vdsusp(CTRLY);
		sig_reset(1);
	}
	else
	{
		sig_handler(1);
		g_env.term.c_lflag &= ~(ECHO | ICANON);
		tputs(g_env.tc->key[0], 1, ft_putchar);
		set_term_vdsusp(_POSIX_VDISABLE);
	}
	if ((tcsetattr(g_env.t_fd, TCSANOW, &(g_env.term))) == -1)
		sh_errorterm(TBADFD);
}

static void		sh_initerm(void)
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

void			sh_configterm(int argc)
{
	if (isatty(STDIN_FILENO) && argc < 2)
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
	set_term_vdsusp(_POSIX_VDISABLE);
	g_env.term.c_lflag &= ~(ICANON | ECHO);
	if ((tcsetattr(g_env.t_fd, TCSANOW, &(g_env.term))) == -1)
		sh_errorterm(TBADFD);
	caps_active_termcaps();
}
