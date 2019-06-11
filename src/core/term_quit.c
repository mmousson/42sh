/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_quit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:04:00 by hben-yah          #+#    #+#             */
/*   Updated: 2019/06/11 15:16:17 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

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
	auto_free();
	line_delenv();
	exit(error);
}
