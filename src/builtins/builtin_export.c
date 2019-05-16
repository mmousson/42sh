/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 05:42:31 by mmousson          #+#    #+#             */
/*   Updated: 2019/05/14 07:32:27 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

/*
**	Function to print an error message when an invalid option is caught, along
**	with the usage information, all on Standard Error Output (2)
**
**	Arguments:
**	caught_invalid_option -> The actual bad option character
**
**	Return Value: ALWAYS (-1)
*/

static int	usage(char caught_invalid_option)
{
	ft_putstr_fd("42sh: export: -", STDERR_FILENO);
	ft_putchar_fd(caught_invalid_option, STDERR_FILENO);
	ft_putendl_fd(": invalid option", STDERR_FILENO);
	ft_putendl_fd("export: usage: export [-p] [--] [arg ...]",
		STDERR_FILENO);
	return (-1);
}

/*
**	This function parses the possible options provided to this utility
**
**	Arguments:
**	argc -> The arguments count
**	argv -> The arguments array
**	parsed -> An int pointer which will be used in the main function to know
**		how many arguments have been read and parsed, so the main function will
**		skip them
**
**	Return Value:
**	(-1)   -> Invalid option provided
**	(>= 0) -> The options have been successfully parsed
*/

static int	parse_options(int argc, char **argv, int *parsed)
{
	int	i;
	int	j;
	int	options;

	options = 0;
	while (++(*parsed) < argc)
	{
		if (ft_strequ(argv[*parsed], "--"))
			return (options);
		else if (argv[*parsed][0] == '-')
		{
			i = 0;
			while (argv[*parsed][++i] != '\0')
			{
				j = 0;
				while (OPTIONS[j] != '\0' && argv[*parsed][i] != OPTIONS[j])
					j++;
				if (OPTIONS[j] == '\0')
					return (usage(argv[*parsed][i]));
				options |= 1 << j;
			}
		}
		else
			return (options);
	}
	return (options);
}

/*
**
*/

static int	export_var(char *def, char ***env)
{
	char	*equal_sign;
	char	*name;

	if ((equal_sign = ft_strchr(def, '=')) != NULL)
	{
		if ((name = ft_strsub(def, 0, (ptrdiff_t)(equal_sign - def))) == NULL)
		{
			ft_putendl_fd("Internal Malloc Error", STDERR_FILENO);
			return (EXPORT_ERROR);
		}
		utility_add_entry_to_environ(env, name, def + ft_strlen(def) + 1);
		utility_set_var(name, def + ft_strlen(name) + 1, env, EXPORT);
		ft_strdel(&name);
	}
	else if ((name = utility_internal_var_exists(def, NULL)) != NULL)
		utility_add_entry_to_environ(env, def, name);
	return (EXPORT_OK);
}

/*
**
*/

static int	list_vars(char **env)
{
	int	i;

	i = -1;
	while (env[++i] != NULL)
	{
		ft_putstr("export ");
		ft_putendl(env[i]);
	}
	return (EXPORT_OK);
}

/*
**
*/

int			blt_export(int argc, char **argv, char ***env)
{
	int	i;
	int	ret;
	int	options;
	int	parsed;

	i = -1;
	parsed = 0;
	ret = EXPORT_OK;
	if (argc == 1)
		return (EXPORT_OK);
	if ((options = parse_options(argc, argv, &parsed)) == -1)
		return (EXPORT_INVALID_OPTION);
	argc -= parsed;
	argv += parsed;
	if (options & (1 << P_INDEX))
		return (list_vars(*env));
	while (++i < argc)
		ret = (export_var(argv[i], env) || ret) ? EXPORT_ERROR : EXPORT_OK;
	return (ret);
}
