/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_parse_options.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 10:30:44 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/10 16:58:23 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs.h"

static int	option_index(char c)
{
	int i;

	i = 0;
	while (ALLOWED_OPTIONS[i] != '\0')
	{
		if (c == ALLOWED_OPTIONS[i])
			return (i);
		i++;
	}
	return (-1);
}

int			parse_options(int argc, char **argv, int *parsed)
{
	int	i;
	int	index;
	int	ret;

	ret = 0;
	while (argc > 0 && !ft_strequ(argv[0], "--") && argv[0][0] == '-')
	{
		i = 0;
		(*parsed)++;
		while (argv[0][++i] != '\0')
			if ((index = option_index(argv[0][i])) == -1)
			{
				ft_putstr_fd("42sh: jobs: -", STDERR_FILENO);
				ft_putchar_fd(argv[0][i], STDERR_FILENO);
				ft_putendl_fd(": invalid option", STDERR_FILENO);
				ft_putendl_fd("jobs: usage: jobs [-l|-p] [job_id...]", 2);
				return (-1);
			}
			else
				ret = 1 << index;
		argc--;
		argv++;
	}
	return (ret);
}
