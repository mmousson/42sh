/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 04:26:47 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/25 12:49:50 by roliveir         ###   ########.fr       */
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

int					main(int argc, char **argv, char **arge_sys)
{
	char			*line;
	int				ret;
	char			**arge;
	
	(void)argc;
	arge = duplicate_environ(arge_sys);
	ft_bzero(&g_env, sizeof(t_env));
	ft_term_manager();
	if (init_job_ctrl(&shell_term_conf) == -1)
		return (128);
	alias_init();
	ret = 1;
	while (ret)
	{
		line = ft_get_line(PBASIC, argv[1]);
		ret = !ft_lex(&line, &g_env, &arge);
		if (ret && line)
		{
			free(line);
			line = NULL;
		}
		if (!g_env.isatty)
			ret = 0;
	}
	ft_del_words_tables(&arge);
	ft_quiterm();
	return (0);
}
