/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 19:34:12 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/12 10:07:10 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs.h"

static void	write_status(t_job *current, int options)
{
	if (options & 1 << JOBS_L_INDEX)
	{
		if (job_is_stopped(current))
		{
			ft_putstr("Suspended: ");
			ft_putnbr(current->status);
			ft_putstr("\t\t");
		}
		else if (job_is_completed(current))
		{
			ft_putstr("Done: ");
			ft_putnbr(current->status);
			ft_putstr("\t\t");
		}
		else
			ft_putstr("Running\t\t");
		return ;
	}
	if (job_is_stopped(current))
		ft_putstr("Stopped\t\t");
	else if (job_is_completed(current))
		ft_putstr("Done\t\t");
	else
		ft_putstr("Running\t\t");
}

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

static int	parse_options(int argc, char **argv)
{
	int	i;
	int	index;
	int	ret;

	argc--;
	argv++;
	ret = 0;
	while (argc > 0 && !ft_strequ(argv[0], "--") && argv[0][0] == '-')
	{
		i = 0;
		while (argv[0][++i] != '\0')
			if ((index = option_index(argv[0][i])) == -1)
			{
				ft_putstr_fd("42sh: jobs: -", STDERR_FILENO);
				ft_putchar_fd(argv[0][i], STDERR_FILENO);
				ft_putendl_fd(": invalid option", STDERR_FILENO);
				ft_putendl_fd("jobs: usage: jobs [-l|-p] [job_id...]", STDERR_FILENO);
				return (-1);
			}
			else
				ret = 1 << index;
		argc--;
		argv++;
	}
	return (ret);
}

static void	format_job_info(t_job *head, int options, int i)
{
	if (options == 0 || (options & 1 << JOBS_L_INDEX))
	{
		ft_putchar('[');
		ft_putnbr(i);
		ft_putchar(']');
	}
	if (head->next == NULL && !(options & 1 << JOBS_P_INDEX))
		ft_putchar('+');
	else if (head->next != NULL && head->next->next == NULL
		&& !(options & 1 << JOBS_P_INDEX))
		ft_putchar('-');
	else if (!(options & 1 << JOBS_P_INDEX))
		ft_putchar(' ');
	if (!(options & 1 << JOBS_P_INDEX))
		ft_putchar(' ');
	if (!(options & (1 << JOBS_P_INDEX)))
		ft_putstr("\t");
	if (options & (1 << JOBS_P_INDEX) || options & (1 << JOBS_P_INDEX))
		ft_putnbr(head->pgid);
	if (options && (!(options & (1 << JOBS_P_INDEX))))
		ft_putchar('\t');
	if (!(options & (1 << JOBS_P_INDEX)))
		write_status(head, options);
	if (!(options & (1 << JOBS_P_INDEX)))
		ft_putendl(head->command);
}

int			jobs(int argc, char **argv, char ***env)
{
	int		i;
	int		options;
	t_job	*head;

	(void)env;
	i = 1;
	first_job_set_and_get(&head, GET);
	if (head == NULL)
		return (JOBS_OK);
	if ((options = parse_options(argc, argv)) == -1)
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
