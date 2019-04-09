/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 04:26:47 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/09 19:55:33 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "job_control_42.h"

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
	test->first_process->argv[0] = ft_strdup("/bin/cat");
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
	// test->first_process->next = NULL;

	ft_putendl_fd("Launching job : '/bin/cat -e | /usr/bin/wc -c'", STDOUT_FILENO);

	job_launch(test, FOREGROUND_LAUNCH);

	if (isatty(STDIN_FILENO))
		tcsetattr(STDIN_FILENO, TCSANOW, &shell_term_conf);
	return (0);
}
