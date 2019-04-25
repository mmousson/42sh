/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 14:12:12 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/25 10:45:23 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void				ft_switch_term(int reset)
{
	if (!g_env.tc->tc)
		return ;
	if ((tcgetattr(g_env.t_fd, &(g_env.term))) == -1)
		ft_errorterm(TBADFD);
	if (reset)
	{
		g_env.term.c_lflag |= (ECHO | ICANON);
		ft_reset_signal(1);
	}
	else
	{
		ft_signal_handler(1);
		g_env.term.c_lflag &= ~(ECHO | ICANON);
	}
	if ((tcsetattr(g_env.t_fd, TCSANOW, &(g_env.term))) == -1)
		ft_errorterm(TBADFD);
}

void				ft_errorterm(t_error error)
{
	ft_putstr_fd("21sh: error ID=", STDERR_FILENO);
	ft_putnbr_fd(error, STDERR_FILENO);
	ft_putstr_fd(" Exiting\n", STDERR_FILENO);
	if (error != TBADFD)
	{
		ft_switch_term(1);
		close(g_env.t_fd);
	}
	ft_delenv();
	exit(error);
}

int					ft_quiterm(void)
{
	if (g_env.isatty)
	{
		ft_switch_term(1);
		close(g_env.t_fd);
	}
	ft_delenv();
	exit(0);
}

static void			ft_initerm(void)
{
	int				ret;
	char			*type;

	type = getenv("TERM");
	if (type && (ret = tgetent(NULL, type)) < 1)
		g_env.tc->tc = 0;
	if ((g_env.t_fd = open(ttyname(STDIN_FILENO), O_RDWR)) < 0)
		ft_errorterm(TTTYNAME);
	if (tcgetattr(g_env.t_fd, &(g_env.term)) == -1)
		ft_errorterm(TBADFD);
	ft_update_termsize();
}

void				ft_configterm(void)
{
	if (isatty(STDIN_FILENO))
		g_env.isatty = 1;
	else
		return ;
	ft_initerm();
	if (!ft_addtermcaps(g_env.tc))
		g_env.tc->tc = 0;
	if (!g_env.tc->tc)
		return ;
	g_env.term.c_cc[VMIN] = 1;
	g_env.term.c_cc[VTIME] = 0;
	g_env.term.c_lflag &= ~(ICANON | ECHO);
	if ((tcsetattr(g_env.t_fd, TCSANOW, &(g_env.term))) == -1)
		ft_errorterm(TBADFD);
	ft_active_termcaps();
}
