/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_sigchld_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 02:05:35 by mmousson          #+#    #+#             */
/*   Updated: 2019/05/12 19:19:01 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include "libft.h"
#include "job_control_42.h"

/*
**	Function working like an object in Object-Oriented Programming
**	Its attribute would be the static variable 'first_job', which can
**	be updated or retrieved using the 'SET' or 'GET' flag defined in the
**	includes/job_control_42.h file
**	This variable is meant to represent the Job list's head
**
**	Arguments:
**	to_set_or_get -> A double pointer which will be used differently
**		depending on the 'set_or_get' value
**		In case its value is SET: the static variable hold in the function will
**			save the value of the dereferenced double pointer argument.
**			TLDR; saving a new Job list Head
**		In case its value is GET: the value stored in the static variable hold
**			in the function will be put into the dereferenced double pointer
**			argument. That way, the calling function can easily retrieve
**			its value
**	set_or_get -> The flag which will determine the function's behaviour
**		Its value should be either SET or GET
**
**	Return Value: NONE
*/

void		job_first_job_set_and_get(t_job **to_set_or_get, int set_or_get)
{
	if (set_or_get == SET)
	{
		if (to_set_or_get == NULL || *to_set_or_get == NULL)
			return ;
		active_job_list = *to_set_or_get;
	}
	else if (set_or_get == GET)
	{
		if (to_set_or_get == NULL)
			return ;
		*to_set_or_get = active_job_list;
	}
}

/*
**	Do not define the SIGCHLD-handling function if this SIGNAL does not exist
**	in the current environment
**	That way, the program won't compile and we don't have to fear undefined any
**	behaviour
*/

#ifdef SIGCHLD

/*
**	Function handling Data Update and User Information when a Job has been
**	completed as the user has direct control of the terminal
**	We first display a log message and then remove the completed job
**	from the job list
**
**	Arguments:
**	current -> The Job that have changed status
**	job_last -> A pointer to the last job of the job_list
**	job_next -> A pointer to the job immediatly following the terminated job
**
**	Return Value: NONE
*/

static void	handle_completed_job(t_job *current, t_job **job_last,
	t_job **job_next)
{
	job_inform_user_about_completion(current, COMPLETED_MSG);
	if (*job_last)
		(*job_last)->next = *job_next;
	else
		job_first_job_set_and_get(job_next, SET);
	// job_free(current);
}

/*
**	Function handling Data Update and User Information when a Job has been
**	stopped as the user has direct control of the terminal
**	We first display a log message and then set the last job of the job_list
**	as the current one
**
**	Arguments:
**	current -> The Job that have changed status
**	job_last -> A pointer to the last job of the job_list
**
**	Return Value: NONE
*/

static void	handle_stopped_job(t_job *current, t_job **job_last)
{
	job_inform_user_about_completion(current, STOP_MSG);
	*job_last = current;
}

/*
**	This function handles the SIGCHLD signal when the user has direct control
**	of the terminal
**
**	Arguments:
**	signo (ignored) -> SIGCHLD signal number
**
**	Return Value: NONE
*/

void		job_sigchld_handler(int signo)
{
	t_job	*current;
	t_job	*job_next;
	t_job	*job_last;

	(void)signo;
	job_first_job_set_and_get(&current, GET);
	job_update_status(current);
	job_last = NULL;
	while (current)
	{
		job_next = current->next;
		if (job_is_completed(current))
			handle_completed_job(current, &job_last, &job_next);
		else if (job_is_stopped(current))
			handle_stopped_job(current, &job_last);
		else
			job_last = current;
		current = job_next;
	}
}
#endif
