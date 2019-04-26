/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 04:26:47 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/26 12:05:58 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "job_control_42.h"

#include <unistd.h>
#include "sh42.h"

#include "lex.h"
#include "line_edition.h"

struct termios	shell_term_conf;
int				vi_on = 0;
t_vars			*shell_var_list = NULL;

/*
**
*/

int					main(int argc, char **argv, char **arge_sys)
{
	int				ret;
	char			*line;
	char			**env;

	(void)argc;
	ret = 1;
	if (init_job_ctrl(&shell_term_conf) == -1)
		return (128);
	alias_init();
	env = duplicate_environ(arge_sys);
	ft_bzero(&g_env, sizeof(t_env));
	ft_term_manager();
	while (ret)
	{
		line = ft_get_line(PBASIC, argv[1]);
		ret = !ft_lex(&line, &g_env, &env);
		if (ret && line)
			ft_strdel(&line);
		if (!g_env.isatty)
			ret = 0;
	}
	ft_del_words_tables(&env);
	ft_quiterm();
	return (0);
}
