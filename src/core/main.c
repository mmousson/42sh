/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 04:26:47 by mmousson          #+#    #+#             */
/*   Updated: 2019/05/31 22:23:03 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "job_control_42.h"

#include <unistd.h>
#include "sh42.h"

#include "lex.h"
#include "libft.h"
#include "line_edition.h"

struct termios	shell_term_conf;
int16_t			g_current_ret = -1;
uint8_t			g_last_ret = 0;
t_vars			*g_shell_var_list = NULL;
t_vars			*g_shell_tmp_vars = NULL;
t_job			*g_active_job_list = NULL;

/*
**
*/

static int			usage(char detected_invalid_option)
{
	ft_putstr_fd("42sh: -", STDERR_FILENO);
	ft_putchar_fd(detected_invalid_option, STDERR_FILENO);
	ft_putendl_fd("\nUsage: 42sh [-c COMMAND_LINE] ...", STDERR_FILENO);
	return (-1);
}

/*
**
*/

static int			parse_options(int ac, char **av, int current, int options)
{
	int	i;
	int	j;

	while (++current < ac)
	{
		if (ft_strequ(av[current], "--"))
			return (options);
		else if (av[current][0] == '-')
		{
			i = 0;
			while (av[current][++i] != '\0')
			{
				j = 0;
				while (SH_OPTS[j] != '\0' && av[current][i] != SH_OPTS[j])
					j++;
				if (SH_OPTS[j] == '\0')
					return (usage(av[current][i]));
				options |= 1 << j;
			}
		}
		else
			return (options);
	}
	return (options);
}

/*
**
*/

static void			loop_on_input(int argc, char **argv, char ***env)
{
	int		ret;
	char	*line;

	ret = 1;
	(void)argc;
	while (ret)
	{
		job_sigchld_handler(0);
		utility_flush_tmp_vars();
		line = line_get_readline(PBASIC, argv[1]);
		// line = ft_strdup("name=value");
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

/*
**
*/

int					main(int argc, char **argv, char **arge_sys)
{
	char			*tmp;
	char			**env;
	int				options;

	if ((options = parse_options(argc, argv, 0, 0)) == -1)
		return (INVALID_OPTION);
	init_alias();
	env = utility_duplicate_environ(arge_sys);
	if (init_job_ctrl() == -1)
		return (128);
	tmp = ft_itoa(getpid());
	core_spec_var_setget(SPEC_0, argv[0], SET);
	core_spec_var_setget(SPEC_UNDERSCORE, argv[0], SET);
	core_spec_var_setget(SPEC_DOLLAR, tmp, SET);
	core_spec_var_setget(SPEC_QUESTION, "0", SET);
	ft_strdel(&tmp);
	ft_bzero(&g_env, sizeof(t_env));
	ft_bzero(&g_data, sizeof(t_autodata));
	sh_term_manager(&env, argc);
	if ((options >> C_OPTION_OFFSET) & 1)
		lex_str(&argv[2], &env);
	else
		loop_on_input(argc, argv, &env);
	tcsetattr(STDIN_FILENO, TCSANOW, &shell_term_conf);
	blt_exit(1, NULL, &env);
	return (g_last_ret);
}
