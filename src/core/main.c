/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 04:26:47 by mmousson          #+#    #+#             */
/*   Updated: 2019/05/09 15:11:34 by oboutrol         ###   ########.fr       */
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
	line = ft_itoa(getpid());
	ft_bzero(&g_env, sizeof(t_env));
	if (init_job_ctrl(&shell_term_conf) == -1)
		return (128);
	/*
<<<<<<< HEAD
	init_alias();
	env = utility_duplicate_environ(arge_sys);
	core_spec_var_setget(SPEC_0, argv[0], SET);
	core_spec_var_setget(SPEC_UNDERSCORE, argv[0], SET);
	core_spec_var_setget(SPEC_DOLLAR, line, SET);
	ft_term_manager();
	ft_strdel(&line);
	// while (ret)
	// {
	// 	line = ft_get_line(PBASIC, argv[1]);
	// 	ret = !ft_lex(&line, &g_env, &env);
	// 	if (ret && line)
	// 		ft_strdel(&line);
	// 	if (!g_env.isatty)
	// 		ret = 0;
	// }
	//============ TESTING ============
	(void)line;
	(void)argv;
	t_job		*ptr;
	t_job		*test;
	// t_job		second_job;
	t_process	*first_process;
	t_process	*second_process;
	// t_process	third_process;
	// t_process	fourth_process;
	char		*job1_command = "cat | wc -c";
	char		*job1_first_proc_argv[] = {"cat", "-e", NULL};
	char		*job1_second_proc_argv[] = {"wc", "-c", NULL};
	// char		*job2_command = "ls bleu vert rouge | cat -e";
	// char		*job2_first_proc_argv[] = {"ls", "bleu", "vert", "rouge", NULL};
	// char		*job2_second_proc_argv[] = {"cat", "-e", NULL};
	test = ft_memalloc(sizeof(t_job));
	first_process = ft_memalloc(sizeof(t_process));
	second_process = ft_memalloc(sizeof(t_process));

	ptr = test;
	test->pgid = 0;
	test->command = ft_strdup(job1_command);
	test->io_channels.input = 0;
	test->io_channels.output = 1;
	test->io_channels.error = 2;
	test->notified = false;
	test->first_process = first_process;
	test->next = NULL;//&second_job;

	test->first_process->argv = utility_duplicate_environ(job1_first_proc_argv);
	test->first_process->environ = &env;
	test->first_process->io_channels.input = 0;
	test->first_process->io_channels.output = 1;
	test->first_process->io_channels.error = 2;
	test->first_process->next = second_process;

	test->first_process->next->argv = utility_duplicate_environ(job1_second_proc_argv);
	test->first_process->next->environ = &env;
	test->first_process->next->io_channels.input = 0;
	test->first_process->next->io_channels.output = 1;
	test->first_process->next->io_channels.error = 2;

	test->first_process->next->next = NULL;

	// second_job.pgid = 0;
	// second_job.command = ft_strdup(job2_command);
	// second_job.io_channels.input = 0;
	// second_job.io_channels.output = 1;
	// second_job.io_channels.error = 2;
	// second_job.notified = false;
	// second_job.first_process = &third_process;
	// second_job.next = NULL;

	// second_job.first_process->argv = utility_duplicate_environ(job2_first_proc_argv);
	// second_job.first_process->environ = &env;
	// second_job.first_process->io_channels.input = 0;
	// second_job.first_process->io_channels.output = 1;
	// second_job.first_process->io_channels.error = 2;
	// second_job.first_process->next = &fourth_process;

	// second_job.first_process->next->argv = utility_duplicate_environ(job2_second_proc_argv);
	// second_job.first_process->next->environ = &env;
	// second_job.first_process->next->io_channels.input = 0;
	// second_job.first_process->next->io_channels.output = 1;
	// second_job.first_process->next->io_channels.error = 2;

	// second_job.first_process->next->next = NULL;

	// test.next = NULL;
	// test.first_process->next = NULL;

	while (ptr != NULL)
	{
		job_launch(ptr, FOREGROUND_LAUNCH);
		ptr = ptr->next;
=======
	*/
	init_alias();
	env = utility_duplicate_environ(arge_sys);
	ft_bzero(&g_env, sizeof(t_env));
	sh_term_manager();
	ret = 1;
	while (ret)
	{
		line = line_get_readline(PBASIC, argv[1]);
		ret = !lex_str(&line, &env);
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
