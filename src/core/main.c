/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 04:26:47 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/10 03:30:22 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "job_control_42.h"

#include <signal.h>
#include <unistd.h>
#include <termios.h>
#include "sh42.h"

struct termios	shell_term_conf;

int				main(int argc, char **argv)
{
	t_job	*test;

	(void)argc;
	(void)argv;
	if (init_job_ctrl(&shell_term_conf) == -1)
		return (128);

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

	ft_putendl_fd("Launching job : '/bin/cat -e | /usr/bin/wc -c'", STDOUT_FILENO);

	first_job_set_and_get(&test, SET);

	job_launch(test, FOREGROUND_LAUNCH);
	ft_putendl_fd("fg", STDERR_FILENO);
	if (test->notified)
		unstop_job(test, FOREGROUND_LAUNCH);
	ft_putendl_fd("bg", STDERR_FILENO);
	if (test->notified)
		unstop_job(test, BACKGROUND_LAUNCH);
	ft_putendl_fd("pkill cat wc", STDERR_FILENO);
	signal(SIGCHLD, sigchld_handler);
	kill(-(test->pgid), SIGTERM);
	sleep(5);
	if (isatty(STDIN_FILENO))
		tcsetattr(STDIN_FILENO, TCSANOW, &shell_term_conf);
	return (0);
}
