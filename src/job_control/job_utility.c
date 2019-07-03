/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_utility.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 06:07:12 by mmousson          #+#    #+#             */
/*   Updated: 2019/07/03 16:17:55 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <signal.h>
#include "libft.h"
#include "job_control_42.h"

/*
**	Function computing the number of strings contained in an array (char **)
**	Hence the name 'argc' => Arg count
**
**	Arguments:
**	argv -> The array of strings to count the number of elements from
**
**	Return Value: The computed argc count
*/

int		job_argc(char **argv)
{
	int	res;

	res = 0;
	while (argv[res] != NULL)
		res++;
	return (res);
}

/*
**	Find the active job with the indicated pgid.
**
**	This function returns the active job associated with the specified pgid
**
**	Arguments:
**	pgid      -> The Group ID where to search a job for
**	first_job -> A pointer to the job list's head
**
**	Return Value:
**	NULL     -> No job associated with the specified 'pgid'
**	not NULL -> Pointer to the active job associated with the specified 'pgid'
*/

t_job	*find_job(pid_t pgid, t_job *first_job)
{
	t_job	*current_job;

	current_job = first_job;
	while (current_job)
	{
		if (current_job->pgid == pgid)
			return (current_job);
		current_job = current_job->next;
	}
	return (NULL);
}

/*
**	Checks whether the specified job has stopped
**
**	Arguments:
**	j -> The job to check about being stopped
**
**	Return Value:
**	0 -> The job still has running processes
**	1 -> The job has stopped
*/

int		job_is_stopped(t_job *j, int action)
{
	t_process	*p;

	p = j->first_process;
	while (p)
	{
		if (!p->completed && !p->stopped)
			return (0);
		p = p->next;
	}
	j->status = 18;
	if (action == SAVE_CONF)
		tcgetattr(STDIN_FILENO, &j->tmodes);
	return (1);
}

/*
**	This functions if a job has completed by verifying if all
**	the processes in that jobhave completed
**
**	Arguments:
**	j -> The job to check about completion
**
**	Return Value:
**	0 -> There are still running processes in the job 'j'
**	1 -> The job has completed
*/

int		job_is_completed(t_job *j, int action)
{
	t_process	*p;
	int			status;

	status = 0;
	p = j->first_process;
	while (p)
	{
		if (!p->completed)
			return (0);
		status = p->status;
		p = p->next;
	}
	j->status = WTERMSIG(status);
	if (action == FREE_JOB)
		job_free(j);
	return (1);
}

/*
**	Function designed to format information message display regarding stopped
**	or terminated processes
**	The function returns and does nothing if said informations have already
**	notified
**
**	Arguments:
**	j -> Pointer to Data_structure representing the Job that has stopped or
**	terminated
**	msg -> Additionnal message to display
**
**	Return Value: NONE
*/

void	job_inform_user_about_completion(t_job *j, char *msg)
{
	// t_process	*proc;

	if (j == NULL || (j != NULL && j->notified))
		return ;
	// if (j->first_process->compound)
	// {
	// 	proc = j->first_process;
	// 	while (proc != NULL)
	// 	{
	// 		if (proc->compound)
	// 			kill(proc->pid, SIGUSR1);
	// 		proc = proc->next;
	// 	}
	// 	job_free(j);
	// 	return ;
	// }
	ft_putstr_fd("\nJob '", STDERR_FILENO);
	ft_putstr_fd(j->command, STDERR_FILENO);
	ft_putstr_fd("' has ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	j->notified = true;
	if (ft_strequ(msg, STOP_MSG))
		tcgetattr(STDIN_FILENO, &(j->tmodes));
}
