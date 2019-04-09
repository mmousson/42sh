/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_engine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 02:19:56 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/09 23:22:34 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "libft.h"
#include "job_control_42.h"

/*
**	Function to setup pipe redirection (STDIN & STDOUT)
**	If a pipe syscall fails, display an error message and make the shell exit
**
**	Arguments:
**	job -> The job that is being launched
**	process -> the next-to-be-launched process
**	p -> int array to store Writing and Reading end of the pipe
**
**	Return Value: NONE
*/

static void				pipe_setup(t_job *job, t_process *process, int p[2])
{
	if (process->next)
	{
		if (pipe(p) == -1)
		{
			ft_putendl_fd("Pipe Failed", STDERR_FILENO);
			exit(126);
		}
		else
			process->io_channels.output = p[1];
	}
	else
		process->io_channels.output = job->io_channels.output;
}

/*
**	Function responsible of clearing the pipe redirection if one have been made
**	We verify that by checking if the job's expected I/O channels are different
**	from the current process I/O channels
**	Finally, if there's a next process to launch, make it read from the Reading
**	end of the pipe
**
**	Arguments:
**	job -> The job that is being launched
**	process -> the next-to-be-launched process
**	p -> int array to store Writing and Reading end of the pipe
**
**	Return Value: NONE
*/

static void				pipe_cleanup(t_job *job, t_process *process, int p[2])
{
	if (process->io_channels.input != job->io_channels.input)
		close(process->io_channels.input);
	if (process->io_channels.output != job->io_channels.output)
		close(process->io_channels.output);
	if (process->next)
		process->next->io_channels.input = p[0];
}

/*
**	Function that makes the parent wait for all the processes in a job to
**	complete
**
**	Arguments:
**	job -> A pointer to the Data-Structure holding the informations about
**		the job that has to be waited for
**
**	Return Value: NONE
*/

int					wait_job_completion(t_job *job)
{
	int		ret;
	pid_t pid;

	ret = 0;
	while (42)
	{
		pid = waitpid (WAIT_ANY, &ret, WUNTRACED);
		if (!(!mark_process_status (job, pid, ret)
			&& !job_is_stopped (job)
			&& !job_is_completed (job)))
			break ;
	}
	return (ret);
}

/*
**	Job Control's core function
**	It launches all the processes contained in a job
**
**	Arguments:
**	job -> A pointer to the Data-Structure holding the informations about
**		the job that's about to be launched
**	fg -> A boolean value to determine whether the job has be send
**		to foreground or to background
**
**	Return Value: Return value of the last process in the job
*/

int						job_launch(t_job *job, int fg)
{
	int			p[2];
	pid_t		pid;
	t_process	*current_process;

	current_process = job->first_process;
	while (current_process)
	{
		pipe_setup(job, current_process, p);
		if ((pid = fork()) == 0)
			child_process(current_process, fg, job->pgid);
		else if (pid > 0)
			parent_process(job, current_process, pid);
		else
			ft_putendl_fd("Fork Failed", STDERR_FILENO);
		pipe_cleanup(job, current_process, p);
		current_process = current_process->next;
	}
	if (!isatty(STDIN_FILENO))
		return (wait_job_completion(job));
	else if (fg)
		return (send_job_to_foreground(job, START_JOB));
	else
		return (send_job_to_background(job, START_JOB));
}
