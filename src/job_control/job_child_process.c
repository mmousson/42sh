/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_child_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 21:44:15 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/29 21:44:15 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include "sh42.h"
#include "libft.h"
#include "job_control_42.h"

/*
**	Set back the child's Job Control handlers to default
**	That way, they will not be ignored by inheriting the shell's behaviour
**
**	Arguments: NONE
**
**	Return Value: NONE
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
**
**	Arguments:
**	input -> Target input file descriptor channel
**	output -> Target output file descriptor channel
**	error -> Target error output file descriptor channel
**
**	Return Value: NONE
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
**	non-intercatively, there's nothing to worry about and nothing to do
**
**	We setup the redirection of I/O channels right before calling execve
**	so we can support multiple redirection in a single job
**
**	Finally, if the syscall 'execve' fails, we display an error message and
**	exit with error code 126 (Complying with POSIX Standard)
**	Note: Having execve fail at that point will cause a memory leak which can
**	NOT be prevented
**
**	Arguments:
**	proc -> The Data Structure representing the process to launch
**	pgid -> The ID of the process group being child of the shell
**		if 'pgid' == 0, then the process becomes the Process Group Leader
**		and its ID becomes the Process Group ID
**	io_chan -> Data structure holding Target I/O channels infos
**
**	Return Value: NONE
*/

void		job_child_process(t_job *job, t_process *proc, int foreground, pid_t pgid)
{
	int				blt_pos;
	pid_t			child_id;
	t_bool			interactive;
	t_io_channels	io_chan;
	t_process		*current;

	current = job->first_process;
	io_chan = proc->io_channels;
	interactive = isatty(0);
	if (interactive)
	{
		child_id = getpid();
		if (pgid == 0)
			pgid = child_id;
		setpgid(child_id, pgid);
		if (foreground)
			tcsetpgrp(STDIN_FILENO, pgid);
		reset_signals_actions();
	}
	while (current && current->next)
	{
		close(current->p[0]);
		current = current->next;
	}
	setup_redirections(io_chan.input, io_chan.output, io_chan.error);
	if ((blt_pos = utility_is_builtin(proc->argv[0])) == -1)
	{
		execve(proc->argv[0], proc->argv, *(proc->environ));
		ft_putstr_fd("Failed to execute process: ", STDERR_FILENO);
		ft_putendl_fd(proc->argv[0], STDERR_FILENO);
		ft_putendl_fd("Reason: The file is marked as executable but could not "
			"be run by the operating system", STDERR_FILENO);
		exit(126);
	}
	else
		exit(g_builtins[blt_pos].handler(
				job_argc(proc->argv),
				proc->argv,
				proc->environ));
}
