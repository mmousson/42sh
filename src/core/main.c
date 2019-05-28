/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 04:26:47 by mmousson          #+#    #+#             */
/*   Updated: 2019/05/28 09:14:48 by oboutrol         ###   ########.fr       */
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
int16_t			g_current_ret = -1;
uint8_t			g_last_ret = 0;
t_vars			*g_shell_var_list = NULL;
t_job			*g_active_job_list = NULL;

/*
**
*/

#include "libft.h"
int					main(int argc, char **argv, char **arge_sys)
{
	char			*line;
	char			**env;
	int				ret;

	(void)argc;
	ret = 1;
	init_alias();
	env = utility_duplicate_environ(arge_sys);
	if (init_job_ctrl() == -1)
		return (128);
	line = ft_itoa(getpid());
	core_spec_var_setget(SPEC_0, argv[0], SET);
	core_spec_var_setget(SPEC_UNDERSCORE, argv[0], SET);
	core_spec_var_setget(SPEC_DOLLAR, line, SET);
	ft_strdel(&line);
	ft_bzero(&g_env, sizeof(t_env));
	ft_bzero(&g_data, sizeof(t_autodata));
	sh_term_manager(&env);
	while (ret)
	{
		job_sigchld_handler(0);
		line = line_get_readline(PBASIC, argv[1]);
		// line = ft_strdup("ls | ls > file");
		tcsetattr(STDIN_FILENO, TCSADRAIN, &shell_term_conf);
		ret = !lex_str(&line, &env);
		g_last_ret = g_current_ret;
		g_current_ret = -1;
		if (ret && line)
			ft_strdel(&line);
		if (!g_env.isatty)
			ret = 0;
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &shell_term_conf);
	blt_exit(1, NULL, NULL);
	return (0);
}
