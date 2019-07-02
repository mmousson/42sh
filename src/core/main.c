/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 04:26:47 by mmousson          #+#    #+#             */
/*   Updated: 2019/07/02 12:23:09 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control_42.h"
#include "sh42.h"
#include "lex.h"

struct termios	shell_term_conf;
int16_t			g_current_ret = -1;
uint8_t			g_last_ret = 0;
t_vars			*g_shell_var_list = NULL;
t_vars			*g_shell_tmp_vars = NULL;
t_job			*g_active_job_list = NULL;

static void			loop_on_input(int argc, char **argv, char ***env)
{
	int		ret;
	char	*line;

	ret = 1;
	line = NULL;
	(void)argc;
	while (ret)
	{
		job_sigchld_handler(0);
		line = line_get_readline(PBASIC, argv[1]);
		lex_add_hist(&line, 0);
		tcsetattr(STDIN_FILENO, TCSADRAIN, &shell_term_conf);
		ret = !lex_str(&line, env);
		g_last_ret = g_current_ret;
		g_current_ret = -1;
		if (ret && line)
			ft_strdel(&line);
		if (!g_env.isatty)
			ret = 0;
	}
}

static void			bootup(int argc, char **argv, char ***env)
{
	char	*tmp;

	if ((tmp = ft_itoa(getpid())) == NULL)
		ft_putendl_fd("42sh: bootup: Internal Malloc Error", STDERR_FILENO);
	core_spec_var_setget(SPEC_0, argv[0], SET);
	core_spec_var_setget(SPEC_UNDERSCORE, argv[0], SET);
	core_spec_var_setget(SPEC_DOLLAR, tmp, SET);
	core_spec_var_setget(SPEC_QUESTION, "0", SET);
	ft_strdel(&tmp);
	ft_bzero(&g_env, sizeof(t_env));
	ft_bzero(&g_data, sizeof(t_autodata));
	sh_term_manager(env, argc);
}

int					main(int argc, char **argv, char **arge_sys)
{
	char			**env;
	char			*c_arg;

	c_arg = NULL;
	if (core_parse_options(argc, argv, &c_arg) == -1)
		return (INVALID_OPTION);
	init_alias();
	env = utility_duplicate_environ(arge_sys);
	if (init_job_ctrl() == -1)
		return (128);
	bootup(argc, argv, &env);
	if (c_arg != NULL)
		lex_str(&c_arg, &env);
	else
		loop_on_input(argc, argv, &env);
	blt_exit(1, NULL, &env);
}
