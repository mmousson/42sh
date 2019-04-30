/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_mark_process_status.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 21:45:33 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/30 02:17:34 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "libft.h"
#include "job_control_42.h"

/*
**	This function will loop through the lookup table defined in the
**	job_control/sig_table.c file to look for the appropriate message to display
**	depending on the SIGNAL that the child process received
**
**	Arguments:
**	signo -> The signal number to search a message for
**
**	Return Value: NONE
*/

static void				print_sig_def(int signo)
{
	t_sig_matcher	*ptr;

	ptr = g_sig_table;
	while (ptr->msg != NULL)
	{
		if (ptr->signo == signo)
		{
			ft_putstr_fd(ptr->sig_name, STDERR_FILENO);
			ft_putstr_fd(" (", STDERR_FILENO);
			ft_putstr_fd(ptr->msg, STDERR_FILENO);
			ft_putstr_fd(")\n", STDERR_FILENO);
			return ;
		}
		ptr++;
	}
	ft_putendl_fd("Undefined SIGNAL", STDERR_FILENO);
}

/*
**	Function to display all needed informations about a process terminated by
**	a SIGNAL, namely:
**	Process ID, Process Name and Job Name followed by
**	SIGNAL name and informations
**
**	Arguments:
**	proc -> A pointer to the Data-Structure representing the terminated process
**	cmd -> The command line backup representing the Job
**	status -> The value returned by the terminated process
**
**	Return Value: NONE
*/

void					format_process_info(t_process *proc, char *cmd,
	int status)
{
	char	*tmp;

	tmp = ft_itoa(WIFSIGNALED(status) ? 128 + WTERMSIG(status) : status % 255);
	core_spec_var_setget(SPEC_QUESTION, tmp, SET);
	ft_strdel(&tmp);
	if (!WIFSIGNALED(status))
		return ;
	ft_putstr_fd("\n42sh: Process ", STDERR_FILENO);
	ft_putnbr_fd(proc->pid, STDERR_FILENO);
	ft_putstr_fd(", '", STDERR_FILENO);
	ft_putstr_fd(proc->argv[0], STDERR_FILENO);
	ft_putstr_fd("' in job '", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd("' terminated by signal: ", STDERR_FILENO);
	print_sig_def(WTERMSIG(status));
}

/*
**	Function completing the work accomplished by the 'job_mark_process_status'
**	function below
**	Stop the loop once a process with a pid matching the 'pid' argument has
**	been found, and update the 't_process' Data-Structure accordingly
**	If the process has been terminated by a signal, display the corresponding
**	log message (print_sig_def)
**
**	Arguments:
**	job -> A pointer to the currently checked Job of the current Job List
**	pid -> The pid of the child process that has either stopped or terminated
**	status -> The return value caught by the 'waitpid' syscall, which will be
**		used to search an appropriate log message in the lookup table defined
**		in the job_control/sig_table.c file
**
**	Return Value:
**	0 -> A match has been found and the correpsonding process's data have been
**		updated, everything went fine
**	1 -> No match has been found in the currently searched job
*/

static int				loop_jobs(t_job *job, pid_t pid, int status)
{
	t_process	*proc;

	proc = job->first_process;
	while (proc)
	{
		if (proc->pid == pid)
		{
			proc->status = status;
			if (WIFSTOPPED(status))
			{
				proc->stopped = true;
				job_inform_user_about_completion(job, STOP_MSG);
			}
			else
			{
				proc->completed = true;
				format_process_info(proc, job->command, status);
			}
			return (0);
		}
		proc = proc->next;
	}
	return (1);
}

/*
**	Function called right after a 'waitpid' syscall
**	Once a child process has either terminated or stoppped, this function
**	will search for a process in all the job list with a pid matching the one
**	passed as argument
**	Of course, the search will not occur if the 'waitpid' syscall returned a
**	a value of 0 or -1, which means that something went wrong
**	(or that no child processes are associated with the shell)
**	The actual matching check is done in the function 'loop_jobs' defined above
**
**	Arguments:
**	first_job -> A pointer to the First_job of the current Job List
**	pid -> The pid of the child process that has either stopped or terminated
**	status -> The return value caught by the 'waitpid' syscall, which will be
**		used to search an appropriate log message in the lookup table defined
**		in the job_control/sig_table.c file
**
**	Return Value:
**	0 -> A process with a pid matching the 'pid' argument has been found, and
**		an appropriate message has been displayed to the user, everything OK
**	WAITPID_NO_MATCH (1) -> There's no process with a pid matching the 'pid'
**		argument in the current job_list
**	WAITPID_ERROR (-1) -> 'waitpid' syscall failed, an error occured
*/

int						job_mark_process_status(t_job *first_job, pid_t pid,
	int status)
{
	t_job		*job;

	if (pid > 0)
	{
		job = first_job;
		while (job)
		{
			if (loop_jobs(job, pid, status) == 0)
				return (0);
			job = job->next;
		}
		ft_putstr_fd("No process found with pid: ", STDERR_FILENO);
		ft_putnbr_fd(pid, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		return (WAITPID_NO_MATCH);
	}
	else if (pid == 0)
		return (WAITPID_ERROR);
	else
		return (WAITPID_ERROR);
}
