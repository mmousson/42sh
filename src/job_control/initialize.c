/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 11:33:23 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/07 11:34:31 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

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

int	init_job_ctrl(struct termios *bkp_conf)
{
	int		is_shell_intercative;
	pid_t	shell_pgid;

	is_shell_intercative = isatty(STDIN_FILENO);
	if (is_shell_intercative)
	{
		while (tcgetpgrp(STDERR_FILENO) != (shell_pgid = getpgrp()))
			kill(-shell_pgid, SIGTTIN);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		signal(SIGTTIN, SIG_IGN);
		signal(SIGTTOU, SIG_IGN);
		signal(SIGCHLD, SIG_IGN);
		shell_pgid = getpid();
		if (setpgid(shell_pgid, shell_pgid) < 0)
		{
			write(STDERR_FILENO, "Error initializing the shell", 28);
			return (-1);
		}
		tcsetpgrp(STDIN_FILENO, shell_pgid);
		tcgetattr(STDIN_FILENO, bkp_conf);
	}
	return (1);
}
