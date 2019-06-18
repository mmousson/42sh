/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_initialize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 11:33:23 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/18 10:58:25 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include "job_control_42.h"

pid_t	g_shell_proc_group_id;

/*
**	This functions checks if the shell is launched as an intercative one
**	If so, it enables the job control
**
**	Arguments:
**	bkp_conf -> A pointer to the structure where the function will store
**	the saved terminal configuration if launced interactively
**
**	Return Value (int):
**	1  -> Everything went well
**	-1 -> An error occured
*/

int		init_job_ctrl(void)
{
	int		is_shell_intercative;

	is_shell_intercative = isatty(STDIN_FILENO);
	if (is_shell_intercative)
	{
		while (tcgetpgrp(STDERR_FILENO) != (g_shell_proc_group_id = getpgrp()))
			kill(-g_shell_proc_group_id, SIGTTIN);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		signal(SIGTTIN, SIG_IGN);
		signal(SIGTTOU, SIG_IGN);
		signal(SIGTERM, job_sigterm);
		g_shell_proc_group_id = getpid();
		if (setpgid(g_shell_proc_group_id, g_shell_proc_group_id) < 0)
		{
			write(STDERR_FILENO, "Error initializing the shell", 28);
			return (-1);
		}
		tcsetpgrp(STDIN_FILENO, g_shell_proc_group_id);
		tcgetattr(STDIN_FILENO, &shell_term_conf);
	}
	return (1);
}
