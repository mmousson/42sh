/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 04:26:47 by mmousson          #+#    #+#             */
/*   Updated: 2019/05/08 20:09:08 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

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
	char			*line;
	char			**env;
	int				ret;

	(void)argc;
	ret = 1;
	init_alias();
	if (init_job_ctrl(&shell_term_conf) == -1)
		return (128);
	env = utility_duplicate_environ(arge_sys);
	line = ft_itoa(getpid());
	core_spec_var_setget(SPEC_0, argv[0], SET);
	core_spec_var_setget(SPEC_UNDERSCORE, argv[0], SET);
	core_spec_var_setget(SPEC_DOLLAR, line, SET);
	ft_strdel(&line);
	ft_bzero(&g_env, sizeof(t_env));
	sh_term_manager();
	while (ret)
	{
		line = line_get_readline(PBASIC, argv[1]);
		ret = !ft_lex(&line, &env);
		if (ret && line)
			ft_strdel(&line);
		if (!g_env.isatty)
			ret = 0;
	}
	tcsetattr(STDIN_FILENO, TCSADRAIN, &shell_term_conf);
	ft_del_words_tables(&env);
	sh_quiterm();
	return (0);
}
