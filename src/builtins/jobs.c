/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 19:34:12 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/11 20:06:30 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs.h"

int	jobs(int argc, char **argv, char ***env)
{
	int		i;
	t_job	*current;

	(void)argc;
	(void)argv;
	(void)env;
	first_job_set_and_get(&current, GET);
	if (current == NULL)
		return (0);
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
	return (0);
}
