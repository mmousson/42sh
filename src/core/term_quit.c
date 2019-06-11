/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 14:12:12 by roliveir          #+#    #+#             */
/*   Updated: 2019/06/11 14:51:06 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

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