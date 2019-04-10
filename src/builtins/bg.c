/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 12:02:15 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/10 12:45:25 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bg.h"

/*
**	This function simply checks if the provided job's pgid matches the
**	specified 'jobspec' and if so, wake it up into background
**
**	Arguments:
**	job -> Pointer to a Data-Structure representing the job with to-be-checked
**		pgid
**	jobspec -> The specific value to compare the job's pgid with
**
**	Return Value:
**	1 -> 'jobspec' matches the job's pgid. Job sent to background
**	0 -> No match
*/

static int		check_job(t_job *job, pid_t jobspec)
{
	if (job->pgid == jobspec)
	{
		unstop_job(job, BACKGROUND_LAUNCH);
		return (1);
	}
	else
		return (0);
}

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
**	Function which loops through every job in the job list and stop them if
**	their pgid matches with a 'jobspec' provided in the 'argv' array
**
**	Arguments:
**	current -> The head of the job list
**	argc -> Arguments Count
**	argv -> Arguments Array
**
**	Return Value:
**	BG_JOB_FOUND (0) -> At least one job has to be, and has been stopped
**	BG_NO_SUCH_JOB (1) -> There was no match
*/

static int		format_bg_infos(t_job *current, int argc, char **argv)
{
	int		ret;
	pid_t	tmp;

	ret = BG_NO_SUCH_JOB;
	while (--argc > 0)
	{
		argv++;
		tmp = get_jobspec(argv[0]);
		if (check_job(current, tmp))
			ret = BG_JOB_FOUND;
		else
		{
			ft_putstr_fd("42sh: bg: ", STDERR_FILENO);
			ft_putnbr_fd(tmp, STDERR_FILENO);
			ft_putendl_fd(": There are no suitable jobs", STDERR_FILENO);
		}
	}
	return (ret);
}

/*
**	==================== BUITLIN COMMAND ====================
**	Resume each job 'jobsoec' in the background, as if they have been started
**	with '&'
**	If no argument is provided, the current job is used
**	The builtin shall fail is Job Control is not enabled or when any 'jobspec'
**	was not found
**
**	Return Value:
**	BG_JOB_FOUND (0) -> The job specified by 'jobspec' was correctly found and
**		resumed
**	BG_NO_SUCH_JOB (1) -> No job corresponding to 'jobspec' was found, nothing
**		was sent to background
**	BG_NO_JOB_CONTROL (2) -> The Job Control is disabled
*/

int				bg(int argc, char **argv, char ***env)
{
	t_job	*current;

	(void)env;
	first_job_set_and_get(&current, GET);
	if (argc == 1)
	{
		if (current != NULL)
		{
			unstop_job(current, BACKGROUND_LAUNCH);
			return (BG_JOB_FOUND);
		}
		ft_putendl_fd("42sh: bg: current: There are no suitable jobs", 2);
		return (BG_NO_SUCH_JOB);
	}
	argc--;
	argv++;
	return (format_bg_infos(current, argc, argv));
}
