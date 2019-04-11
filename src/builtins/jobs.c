/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 19:34:12 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/11 20:38:45 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs.h"

static void	usage(char c)
{

}

static int	option_index(char c)
{
	int i;

	i = 0;
	while (ALLOWED_OPTIONS[i] != '\0')
	{
		if (c == ALLOWED_OPTIONS[i])
			return (i);
	}
	return (-1);
}

static int	parse_options(int argc, char **argv)
{
	int	i;
	int	index;
	int	ret;

	argc--;
	argv++;
	ret = 0;
	while (argc > 0 && !ft_strequ(argv[0], "--"))
	{
		i = 0;
		if (argv[0][0] != '-')
			break;
		while (argv[0][++i] != '\0')
		{
			if ((index = option_index(argv[0][i])) == -1)
			{

				return (-1);
			}
			else
				ret |= 1 << index;
		}
	}
	return (ret);
}

int			jobs(int argc, char **argv, char ***env)
{
	int		i;
	int		options;
	t_job	*current;

	(void)env;
	first_job_set_and_get(&current, GET);
	if (current == NULL)
		return (JOBS_OK);
	if ((options = parse_options(argc, argv)) == -1)
		return (JOBS_INVALID_OPTION);
	i = 1;
	ft_putendl("Job\tGroup\tState\tCommand");
	while (current)
	{
		ft_putnbr(i);
		ft_putstr("  \t");
		ft_putnbr(current->pgid);
		ft_putchar('\t');
		ft_putstr(current->notified ? "stopped\t" : "running\t");
		ft_putendl(current->command);
		current = current->next;
	}
	return (JOBS_OK);
}
