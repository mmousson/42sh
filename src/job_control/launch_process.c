/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 09:50:06 by marvin            #+#    #+#             */
/*   Updated: 2019/04/07 09:50:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include "libft.h"
#include "job_control_42.h"

/*
**	Set back the child's Job Control handlers to default
**	That way, they will be ignored by inheriting the shell's behaviour
*/

static void	reset_signals_actions(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
}

/*
**	Handle the redirection of I/O channels
*/

static void	setup_redirections(int input, int output, int error)
{
	if (input != STDIN_FILENO)
	{
		dup2 (input, STDIN_FILENO);
		close (input);
	}
	if (output != STDOUT_FILENO)
	{
		dup2 (output, STDOUT_FILENO);
		close (output);
	}
	if (error != STDERR_FILENO)
	{
		dup2 (error, STDERR_FILENO);
		close (error);
	}
}

/*
**	Main function responsible of launching the processes in a job right after
**	they have been forked
**
**	First, we reset the default signal actions since they have been set to be
**	ignored by the shell when enabling Job Control, and this behaviour will be
**	transmitted to child processes by inheritance. Of course, if we are running
**	non-intercatively, there's nothing to do about it
**
**	We setup the redirection of I/O channels right before calling execve
**	so we can support multiple redirection in a single job
**
**	Finally, if the syscall 'execve' fails, we display an error message and
**	exit with error code 126 (Complying with POSIX Standard)
**	Note: Having execve fail at that point will cause a memory leak which can
**	NOT be prevented
*/

void		child_process(t_process *process, pid_t pgid)
{
	pid_t	child_id;
	t_bool	interactive;

	interactive = isatty(0);
	if (interactive)
	{
		child_id = getpid();
		if (pgid == 0)
			pgid = child_id;
		setpgid(child_id, pgid);
		reset_signals_actions();
	}
	setup_redirections(process);
	execve(process->argv[0], process->argv, process->environ);
	ft_putstr_fd("Failed to execute process: ", STDERR_FILENO);
	ft_putendl_fd(file, STDERR_FILENO);
	ft_putendl_fd("Reason: The file is marked as executable but could not "
		"be run by the operating system", STDERR_FILENO);
	exit(126);
}
