/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 04:26:47 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/14 12:20:05 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "job_control_42.h"

#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <termios.h>
#include "sh42.h"

struct termios	shell_term_conf;

int				main(int argc, char **argv)
{
	t_job	*test;
	char	*fg_argv[] = { "fg" };
	char	*bg_argv[] = { "bg" };
	char	*jobs_argv[] = { "jobs", "12" };
	char	*alias_argv[] = { "alias", "ls=ls -G", "nornor=norminette | grep -C1 Error" };
	char	*unalias_argv[] = { "unalias", "--", "-a" };
	char	*type_argv[] = { "type", "--", "-a", "ls", "ls", "echo" };

	(void)argc;
	(void)argv;

	if (init_job_ctrl(&shell_term_conf) == -1)
		return (128);
	alias_init();

	test = malloc(sizeof(t_job));
	test->pgid = 0;
	test->notified = false;
	test->first_process = malloc(sizeof(t_process));
	test->first_process->next = malloc(sizeof(t_process));
	test->first_process->next->next = NULL;
	test->first_process->environ = NULL;
	test->first_process->next->environ = NULL;
	test->first_process->io_channels.input = 0;
	test->first_process->io_channels.output = 1;
	test->first_process->io_channels.error = 2;
	test->first_process->next->io_channels.input = 0;
	test->first_process->next->io_channels.output = 1;
	test->first_process->next->io_channels.error = 2;
	test->first_process->argv = malloc(sizeof(char *) * 3);
	test->first_process->next->argv = malloc(sizeof(char *) * 3);
	test->first_process->argv[0] = ft_strdup("./a.out");
	test->first_process->argv[1] = ft_strdup("-e");
	test->first_process->argv[2] = NULL;
	test->first_process->next->argv[0] = ft_strdup("/usr/bin/wc");
	test->first_process->next->argv[1] = ft_strdup("-c");
	test->first_process->argv[2] = NULL;
	test->command = ft_strdup("/bin/cat -e | /usr/bin/wc -c");
	test->io_channels.input = 0;
	test->io_channels.output = 1;
	test->io_channels.error = 2;
	test->next = NULL;
	test->first_process->next = NULL;

	ft_putendl_fd("alias ls=\"ls -G\" nornor=\"norminette | grep -C1 Error\"\n", STDERR_FILENO);
	alias(3, alias_argv, NULL);
	ft_putendl_fd("\ntype -- -a ls ls echo\n", STDERR_FILENO);
	type(6, type_argv, NULL);

	ft_putendl_fd("\nunalias -- -a\n", STDERR_FILENO);
	unalias(3, unalias_argv, NULL);

	ft_putendl_fd("Launching job : '/bin/cat -e | /usr/bin/wc -c'", STDOUT_FILENO);

	first_job_set_and_get(&test, SET);

	job_launch(test, FOREGROUND_LAUNCH);

	ft_putendl_fd("\njobs\n", STDERR_FILENO);
	jobs(1, jobs_argv, NULL);
	ft_putchar('\n');
	ft_putendl_fd("jobs 12\n", STDERR_FILENO);
	jobs(2, jobs_argv, NULL);

	ft_putendl_fd("fg", STDERR_FILENO);
	fg(1, fg_argv, NULL);

	ft_putendl_fd("bg", STDERR_FILENO);
	bg(1, bg_argv, NULL);

	ft_putendl_fd("pkill cat wc", STDERR_FILENO);
	signal(SIGCHLD, sigchld_handler);

	kill(-(test->pgid), SIGSEGV);

	sleep(5);
	free_alias_list();
	if (isatty(STDIN_FILENO))
		tcsetattr(STDIN_FILENO, TCSANOW, &shell_term_conf);
	return (0);
}
