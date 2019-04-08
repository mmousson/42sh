/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 04:26:47 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/08 11:42:39 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <termios.h>
#include "sh42.h"

struct termios	shell_term_conf;

int				main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	if (init_job_ctrl(&shell_term_conf) == -1)
		return (128);
	sleep(2);
	if (isatty(STDIN_FILENO))
		tcsetattr(STDIN_FILENO, TCSANOW, &shell_term_conf);
	return (0);
}
