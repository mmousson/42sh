/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 09:32:07 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/10 11:58:17 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fg.h"

/*
**	Simple function to get the jobspec to search a job for
**	This data will be extracted from the argv[1] if provided
**	Any excess argument will be ignored
**	If no argument was provided, return (-1), telling the main function to
**	simply resume the current job
**
**	Return Value:
**	(-1) -> No argument provided, search for current job
**	Any other value -> the jobspec to match for
*/

static pid_t	get_jobspec(char *arg)
{
	if (arg)
		return ((pid_t)ft_atoi(arg));
	else
		return (-1);
}

/*
**	==================== BUITLIN COMMAND ====================
**	Resume the job 'jobspec' in the foreground and make it the current job
**	If no job corresponds to 'jobspec' pid, display an appropriate error
**	message
**
**	Return Value:
**	FG_JOB_FOUND (0) -> The job specified by 'jobspec' was correctly found and
**		resumed
**	FG_NO_SUCH_JOB (1) -> No job corresponding to 'jobspec' was found, nothing
**		was sent to foreground, and the shell still has control over terminal
*/

int				fg(int argc, char **argv, char ***env)
{
	t_job	*current;
	pid_t	jobspec;

	(void)env;
	first_job_set_and_get(&current, GET);
	jobspec = get_jobspec(argc == 1 ? NULL : argv[1]);
	while (current)
	{
		if (jobspec == -1 || current->pgid == jobspec)
		{
			unstop_job(current, FOREGROUND_LAUNCH);
			return (FG_JOB_FOUND);
		}
		current = current->next;
	}
	ft_putstr_fd("42sh: fg: ", STDERR_FILENO);
	if (jobspec != -1)
		ft_putnbr_fd(jobspec, STDERR_FILENO);
	else
		ft_putstr_fd("current", STDERR_FILENO);
	ft_putendl_fd(": There are no suitable jobs", STDERR_FILENO);
	return (FG_NO_SUCH_JOB);
}
