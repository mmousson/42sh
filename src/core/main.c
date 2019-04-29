/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 04:26:47 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/29 22:46:00 by mmousson         ###   ########.fr       */
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
	int				ret;
	char			*line;
	char			**env;

	(void)argc;
	ret = 1;
	if (init_job_ctrl(&shell_term_conf) == -1)
		return (128);
	init_alias();
	env = utility_duplicate_environ(arge_sys);
	ft_bzero(&g_env, sizeof(t_env));
	ft_term_manager();
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
	t_job		test;
	t_job		second_job;
	t_process	first_process;
	t_process	second_process;
	t_process	third_process;
	t_process	fourth_process;
	char		*job1_command = "ls -l -a -F | cat -e";
	char		*job1_first_proc_argv[] = {"cat", NULL, "blue", "vert", "f", NULL};
	char		*job1_second_proc_argv[] = {"cat", "-e", NULL};
	char		*job2_command = "echo bleu vert rouge | cat -e";
	char		*job2_first_proc_argv[] = {"ls", "bleu", "vert", "rouge", NULL};
	char		*job2_second_proc_argv[] = {"cat", "-e", NULL};

	ptr = &test;
	test.pgid = 0;
	test.command = ft_strdup(job1_command);
	test.io_channels.input = 0;
	test.io_channels.output = 1;
	test.io_channels.error = 2;
	test.notified = false;
	test.first_process = &first_process;
	test.next = &second_job;

	test.first_process->argv = utility_duplicate_environ(job1_first_proc_argv);
	test.first_process->environ = &env;
	test.first_process->io_channels.input = 0;
	test.first_process->io_channels.output = 1;
	test.first_process->io_channels.error = 2;
	test.first_process->next = &second_process;

	test.first_process->next->argv = utility_duplicate_environ(job1_second_proc_argv);
	test.first_process->next->environ = &env;
	test.first_process->next->io_channels.input = 0;
	test.first_process->next->io_channels.output = 1;
	test.first_process->next->io_channels.error = 2;

	test.first_process->next->next = NULL;

	second_job.pgid = 0;
	second_job.command = ft_strdup(job2_command);
	second_job.io_channels.input = 0;
	second_job.io_channels.output = 1;
	second_job.io_channels.error = 2;
	second_job.notified = false;
	second_job.first_process = &third_process;
	second_job.next = NULL;

	second_job.first_process->argv = utility_duplicate_environ(job2_first_proc_argv);
	second_job.first_process->environ = &env;
	second_job.first_process->io_channels.input = 0;
	second_job.first_process->io_channels.output = 1;
	second_job.first_process->io_channels.error = 2;
	second_job.first_process->next = &fourth_process;

	second_job.first_process->next->argv = utility_duplicate_environ(job2_second_proc_argv);
	second_job.first_process->next->environ = &env;
	second_job.first_process->next->io_channels.input = 0;
	second_job.first_process->next->io_channels.output = 1;
	second_job.first_process->next->io_channels.error = 2;

	second_job.first_process->next->next = NULL;

	// test.next = NULL;
	// test.first_process->next = NULL;

	while (ptr != NULL)
	{
		job_launch(ptr, FOREGROUND_LAUNCH);
		ptr = ptr->next;
	}

	sleep(1);

	ft_del_words_tables(&env);
	ft_quiterm();
	return (0);
}
