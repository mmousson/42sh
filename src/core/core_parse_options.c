/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_parse_options.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 15:41:05 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/17 11:31:07 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	usage(char detected_invalid_option)
{
	ft_putstr_fd("42sh: -", STDERR_FILENO);
	ft_putchar_fd(detected_invalid_option, STDERR_FILENO);
	ft_putendl_fd(": invalid option", 2);
	ft_putendl_fd("Usage: 42sh [-c COMMAND_LINE] ...", STDERR_FILENO);
	return (-1);
}

static char	*opt_arg(char *cur, char *next)
{
	char	*res;

	res = NULL;
	if (*cur == '\0')
	{
		if (next != NULL && (res = ft_strdup(next)) == NULL)
			ft_putendl_fd("42sh: Internal Malloc Error", STDERR_FILENO);
		else if (next == NULL)
			ft_putendl_fd("42sh: -c: option requires an argument",
															STDERR_FILENO);
	}
	else
	{
		if ((res = ft_strdup(cur)) == NULL)
			ft_putendl_fd("42sh: Internal Malloc Error", STDERR_FILENO);
	}
	return (res);
}

int			core_parse_options(int ac, char **av, char **opts)
{
	int	i;
	int	j;

	j = 0;
	while (++j < ac)
	{
		if (ft_strequ(av[j], "--"))
			return (1);
		else if (av[j][0] == '-')
		{
			i = 0;
			while (av[j][++i] != '\0')
			{
				if (av[j][i] != 'c')
					return (usage(av[j][i]));
				if ((*opts = opt_arg(av[j] + i + 1, av[j + 1])) == NULL)
					return (-1);
			}
		}
		else
			return (1);
	}
	return (1);
}
