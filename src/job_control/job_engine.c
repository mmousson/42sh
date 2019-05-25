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

#include <stdio.h>

#include <sys/wait.h>
#include "libft.h"
#include "sh42.h"
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

static void				pipe_setup(t_process *process)
{
	if (process->next)
	{
		if (pipe(process->p) == -1)
		{
			ft_putendl_fd("Pipe Failed", STDERR_FILENO);
			exit(126);
		}
		else
			process->io_channels.output = process->p[1];
	}
	else
		process->io_channels.output = process->real_channels.output;
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

static void				pipe_cleanup(t_process *process)
{
	if (process->io_channels.input != process->real_channels.input)
		close(process->io_channels.input);
	if (process->io_channels.output != process->real_channels.output)
	{
		printf("Closing %d\n", process->io_channels.output);
		close(process->io_channels.output);
	}
	if (process->next)
		process->next->io_channels.input = process->p[0];
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

int					job_wait_completion(t_job *job, t_process *proc)
{
	t_bool		is_only_builtins;
	int			ret;
	pid_t 		pid;

	ret = 0;
	is_only_builtins = true;
	while (proc != NULL)
	{
		if (proc->valid_to_wait_for == true)
		{
			is_only_builtins = false;
			pid = waitpid(proc->pid, &ret, WUNTRACED);
			if (job_mark_process_status(pid, ret)
				+ job_is_stopped(job, SAVE_CONF)
				+ job_is_completed(job, FREE_JOB) != 0)
				break ;
		}
		else
			ret = proc->status;
		proc = proc->next;
	}
	if (is_only_builtins)
		job_free(job);
	return (ret % 255);
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
	t_process	*current_process;

	current_process = job->first_process;
	while (current_process)
	{
		pipe_setup(current_process);
		job_command_search_and_exec(job, current_process, fg);
		pipe_cleanup(current_process);
		current_process = current_process->next;
	}
	job_add_to_active_job_list(job);
	if (!isatty(STDIN_FILENO))
		return (job_wait_completion(job, job->first_process));
	else if (fg)
		return (job_send_to_foreground(job, START_JOB));
	else
		return (job_send_to_background(job, START_JOB));
}
