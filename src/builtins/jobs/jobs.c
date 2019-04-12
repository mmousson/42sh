/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 19:34:12 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/12 10:34:21 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs.h"

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

int			jobs(int argc, char **argv, char ***env)
{
	int		i;
	int		parsed;
	int		options;
	t_job	*head;

	i = 1;
	parsed = 0;
	(void)env;
	argc--;
	argv++;
	first_job_set_and_get(&head, GET);
	if (head == NULL)
		return (JOBS_OK);
	if ((options = parse_options(argc, argv, &parsed)) == -1)
		return (JOBS_INVALID_OPTION);
	while (head)
	{
		format_job_info(head, options, i);
		ft_putchar('\n');
		head = head->next;
		i++;
	}
	return (JOBS_OK);
}
