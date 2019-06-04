/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 08:12:46 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/04 08:12:46 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fc.h"
#include "sh42.h"

static int			e_option(t_options_infos *holder, char *opt, char *next)
{
	if (*(opt + 1) != '\0')
	{
		holder->editor_name = ft_strdup(opt + 1);
		return (1);
	}
	else if (next != NULL)
	{
		holder->editor_name = ft_strdup(next);
		return (2);
	}
	else
	{
		ft_putendl_fd("42sh: fc: -e: option requires an argument", 2);
		holder->invalid = 1;
		return (-1);
	}
}

/*
**
*/

static int			add_option(t_options_infos *holder, char *opt, char *next)
{
	if (*opt == 'e')
		return (e_option(holder, opt, next));
	else if (*opt == 'l')
		holder->listing = 1;
	else if (*opt == 'n')
		holder->suppressed = 1;
	else if (*opt == 'r')
		holder->reversed = 1;
	else if (*opt == 's' && holder->dash_s == NULL)
	{
		if ((holder->dash_s = ft_memalloc(sizeof(t_reinvoke))) == NULL)
		{
			ft_putendl_fd("42sh: Internal Malloc Error", STDERR_FILENO);
			return (-1);
		}
	}
	else
	{
		ft_putstr_fd("42sh: fc: -", STDERR_FILENO);
		ft_putchar_fd(*opt, STDERR_FILENO);
		ft_putendl_fd(": invalid option", STDERR_FILENO);
		return (-1);
	}
	return (0);
}

/*
**
*/

static int			parse_argument(t_options_infos *res, char **av, char **env)
{
	size_t	i;
	int		ret;

	i = 0;
	(void)env;
	while (av[res->parsed][++i] != '\0')
	{
		ret = add_option(res, av[res->parsed] + i, av[res->parsed + 1]);
		if (ret > 0)
			return (ret - 1);
		else if (ret == -1)
			return (-1);
	}
	return (0);
}

static void			loop(t_options_infos *res, int argc, char **av, char **env)
{
	while (++res->parsed < argc)
	{
		if (ft_strequ(av[res->parsed], "--"))
		{
			res->parsed++;
			return ;
		}
		else if (av[res->parsed][0] == '-')
		{
			res->ret = parse_argument(res, av, env);
			if (res->ret == -1)
				return ;
			res->parsed += res->ret;
		}
		else
			return ;
	}
	return ;
}

/*
**
*/

t_options_infos		*blt_fc_parse_options(int argc, char **av, char **env)
{
	char			*tmp;
	t_options_infos	*res;

	if ((res = ft_memalloc(sizeof(t_options_infos))) == NULL)
	{
		ft_putendl_fd("42sh: Internal Malloc Error", STDERR_FILENO);
		return (NULL);
	}
	loop(res, argc, av, env);
	if (res->editor_name == NULL)
		res->editor_name = ft_strdup("/bin/ed");
	else
	{
		tmp = utility_search(res->editor_name);
		ft_strdel(&res->editor_name);
		res->editor_name = tmp;
	}
	if (res->editor_name == NULL)
	{
		ft_putendl_fd("42sh: Internal Malloc Error", STDERR_FILENO);
		blt_fc_free_memory(res);
		return (NULL);
	}
	return (res);
}
