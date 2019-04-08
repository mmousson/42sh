/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_engine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 02:19:56 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/08 02:19:56 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "job_control_42.h"

/*
**
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
			process->io_channels.output = pipe[1];
	}
	else
		process->io_channels.output = job->io_channels.output;
}

/*
**
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
**
**
**	chan -> A pointer to the Data-Structure holding the I/O channels infos
**		of the next-to-be-launched process
**
**	Return Value: NONE
*/

// static void				io_channels_setup(t_io_channels *chan)
// {

// }

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

static int				wait_job_completion(t_job *job)
{
	int			ret;
	t_process	*process;

	ret = 0;
	process = job->first_process;
	while (process)
	{
		wait(&ret);
		process = process->next;
	}
	return (ret);
}

/*
**	Job Control's core function
**	It lauches all the processes contained in a job
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
		// io_channels_setup(&(current_process->io_channels));
		pipe_setup(job, current_process, p);
		if ((pid = fork()) == 0)
			child_process(current_process, job->pgid, fg);
		else if (pid > 0)
			parent_process(job, pid);
		else
			ft_putendl_fd("Fork Failed", STDERR_FILENO);
		pipe_cleanup();
		current_process = current_process->next;
	}
	if (!isatty(STDIN_FILENO))
		return (wait_job_completion(job));
	else if (fg)
		return (send_job_to_foreground());
	else
		return (send_job_to_background());
}
