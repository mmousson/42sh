/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 19:34:12 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/29 21:42:45 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs.h"

/*
**	Functions which tells if a job specified by an ID in the arguments exists
**	If so, dislay required informations and return (1)
**	Else return (0)
**	The check is done by looping though the entire Job List and checking if
**	the Process Group Leader's ID matches the specified jobspec
**
**	Arguments:
**	head -> A pointer to the head of the current Job List
**	jobspec -> The specified pid extracted from the arguments
**	options -> Int variable holding the parsed options
*/

static int	specific_job_exists(t_job *head, pid_t jobspec, int options)
{
	int	i;

	i = 1;
	while (head)
	{
		if (head->pgid == jobspec)
		{
			format_job_info(head, options, i);
			ft_putchar('\n');
			return (1);
		}
		head = head->next;
		i++;
	}
	return (0);
}

/*
**	Function which lists information about all specified jobs in the arguments
**	For each arguments, we first check that the specified job exists
**	and if not, display an error message an dset the return value of the
**	function to 'JOBS_ERROR'
**	An error doesn't break the loop
**
**	Arguments:
**	head -> A pointer to the head of the current Job List
**	options -> Int variable holding the parsed options
**	argc -> Remainning arguments count after options parsing
**	argv -> Remaining arguments after options parsing
**
**	Return Value:
**	JOBS_OK (0) -> All specified jobs were found and required informations
**		displayed
**	JOBS_ERROR (1) -> One or more specified job(s) were not found
*/

static int	list_specific_jobs(t_job *head, int options, int argc, char **argv)
{
	int		ret;
	pid_t	jobspec;

	ret = JOBS_OK;
	while (argc > 0)
	{
		jobspec = ft_atoi(argv[0]);
		if (!specific_job_exists(head, jobspec, options))
		{
			ft_putstr_fd("42sh: jobs: ", STDERR_FILENO);
			ft_putstr_fd(argv[0], STDERR_FILENO);
			ft_putendl_fd(": There are no suitable jobs", STDERR_FILENO);
			ret = JOBS_ERROR;
		}
		argc--;
		argv++;
	}
	return (ret);
}

/*
**	Function which lists information about all jobs in the current job list
**	The formatting of said informations is done by the function
**	'format job info'
**
**	Arguments:
**	head -> A pointer to the head of the current Job List
**	options -> Int variable holding the parsed options
**
**	Return Value:
**	ALWAYS 0
*/

static int	list_all_jobs(t_job *head, int options)
{
	int	i;

	i = 1;
	while (head)
	{
		format_job_info(head, options, i);
		ft_putchar('\n');
		head = head->next;
		i++;
	}
	return (0);
}

/*
**	============================ BUITLIN COMMAND ============================
**	The jobs utility shall display the status of jobs that were started in the
**	current shell environment
**	When jobs reports the termination status of a job, the shell shall remove
**	its process ID from the list of those known in the
**	"current shell execution environment"
**	NOTE: environ is ignored
**
**	Return Value:
**	JOBS_OK (0) -> Everyhting went well
**	JOBS_ERROR (1) -> Some specified jobspec was not found
**	JOBS_INVALID OPTION (2) -> An invalid option was provided
*/

int			blt_jobs(int argc, char **argv, char ***env)
{
	int		parsed;
	int		options;
	t_job	*head;

	parsed = 0;
	(void)env;
	argc--;
	argv++;
	job_first_job_set_and_get(&head, GET);
	if (head == NULL)
		return (JOBS_OK);
	if ((options = parse_options(argc, argv, &parsed)) == -1)
		return (JOBS_INVALID_OPTION);
	if (argc - parsed == 0)
		return (list_all_jobs(head, options));
	else if (argc - parsed > 0)
		return (list_specific_jobs(head, options, argc, argv));
	else
		return (JOBS_ERROR);
	return (JOBS_OK);
}
