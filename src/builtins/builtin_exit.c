/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 12:06:58 by mmousson          #+#    #+#             */
/*   Updated: 2019/05/24 21:08:58 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh42.h"
#include "line_edition.h"

/*
**
*/

int					blt_exit(int argc, char **argv, char ***env)
{
	if (argc > 2)
	{
		ft_putendl_fd("42sh: exit: Too many arguments", STDERR_FILENO);
		return (1);
	}
	else
	{
		ft_del_words_tables(env);
		if (g_env.isatty)
		{
			sh_switch_term(1);
			close(g_env.t_fd);
		}
		line_delenv();
		utility_free_alias_list();
		utility_free_shell_vars_list();
		exit(argc == 2 ? ft_atoi(argv[1]) : 0);
	}
	return (0);
}
