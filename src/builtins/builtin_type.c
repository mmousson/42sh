/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 10:20:39 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/05 04:38:18 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "type.h"

t_special_vars	g_msg_matcher[] = {
	{ALIAS, " is aliased to "},
	{BUILTIN, " is a shell builtin"},
	{BINARY, " is "},
	{NOT_FOUND, ": not found"},
	{-1, NULL}
};

/*
**	Function to display usage helper in case of error or if
**	asked by the user
**	'ret_value' tells which value we wish to return to the built-in caller
**	'fd' tells on which Output channel we want to write these informations
*/

static int	usage(int ret_value, int fd)
{
	ft_putendl_fd("Usage: type [-a] name ...", fd);
	ft_putchar_fd('\n', fd);
	ft_putendl_fd("The 'type' utility shall indicate how each argument "
		"would be interpreted if used as command name, had its arguments "
		"been given as commands in a strictly POSIX-compliant shell.", fd);
	return (ret_value);
}

/*
**	This functions parses the option of the command
**	Allowed options are: -a || --help
**	If option is --help, returns (-1) after printing corresponding
**	informations
**	If options is -a, 'option_all' flag is set to 1
**	Once all options are read and if no error occured
**	returns the value of 'option_all' flag
**	If a forbidden function is found, returns (-2) after printing usage helper
**	The values (-1) or (-2) or used to exit the main function, and exit code of
**	the main function results from the boolean assertion (ret != -1)
**	That way, the main function returns (1) only in case of error(s)
*/

static int	ft_parse_options(int argc, char **argv, int *option_all)
{
	int	i;

	i = 0;
	*option_all = 0;
	while (++i < argc)
	{
		if (ft_strequ(argv[i], "--help"))
			return (usage(-1, STDOUT_FILENO));
		else if (ft_strequ(argv[i], "--"))
			return (i + 1);
		else
		{
			if (argv[i][0] == '-')
			{
				if (argv[i][1] == 'a')
					*option_all = 1;
				else
					return (usage(-2, STDERR_FILENO));
			}
			else
				return (i);
		}
	}
	return (i);
}

/*
**	This functions concatenates the 'tmp' and 'part3' arguments (if provided)
**	and then prints the result, before freeing the memory
**	Said result is printed of 'fd' Output if no memory error occured
**	Then it returns the passed 'ret_value' argument
*/

static int	msg(char *name, char *answer, int id, int fd)
{
	if (id == NOT_FOUND)
		ft_putstr_fd("42sh: type: ", fd);
	ft_putstr_fd(name, fd);
	if (id <= 3)
		ft_putstr_fd(g_msg_matcher[id].value, fd);
	if (id == ALIAS)
		ft_putchar_fd('`', fd);
	if (answer != NULL)
	{
		if (id == BINARY)
		{
			ft_putstr_fd(answer, fd);
			ft_putchar_fd('/', fd);
			ft_putstr_fd(name, fd);
		}
		else
			ft_putstr_fd(answer, fd);
	}
	ft_putstr_fd((id == ALIAS) ? "`\n" : "\n", fd);
	return (1);
}

/*
**	THe utility function searches for alias definition, built-in definition or
**	presence in binary_paths (in that order)
**	If -a option is present, all results are displayed
**	else only the first match
*/

static int	ft_search(char *name, char **bin_paths, int search_all)
{
	int				i;
	int				ret;
	DIR				*dir;
	struct dirent	*sd;
	char			*alias;

	i = -1;
	ret = 0;
	if ((alias = alias_exists(name)) != NULL)
		ret = msg(name, alias, ALIAS, STDOUT_FILENO);
	if (utility_is_builtin(name) != -1)
		ret = msg(name, NULL, BUILTIN, STDOUT_FILENO);
	if (bin_paths == NULL && ret == 0)
		return (msg(name, NULL, NOT_FOUND, STDERR_FILENO));
	while (bin_paths[++i] != NULL && (ret == 0 || search_all))
		if ((dir = opendir(bin_paths[i])) != NULL)
		{
			while ((sd = readdir(dir)) != NULL && (ret == 0 || search_all))
				if (ft_strequ(sd->d_name, name))
					ret = msg(name, bin_paths[i], BINARY, STDOUT_FILENO);
			closedir(dir);
		}
	if (ret == 0)
		return (msg(name, NULL, NOT_FOUND, STDERR_FILENO));
	return (0);
}

/*
**	Main function for the 'type' built-in command
**	This functions exits if it reads no argument and displays
**	the appropriate message
**	It then parses all the option, if options there are
**	And skips all arguments beginning with '-'
**	Once all thge setup is done, does the actual searching of defintions of the
**	commands tokens by splitting the (char **)paths and looping through all
**	remaining arguments to find any match in, alias list, built-in definition,
**	or location in binary_paths
*/

int			blt_type(int argc, char **argv, char ***env)
{
	int		i;
	int		err;
	int		opts;
	int		option_all;
	char	**paths;

	i = 0;
	err = 0;
	(void)env;
	if (argc <= 1)
		return (usage(1, STDERR_FILENO));
	if ((opts = ft_parse_options(argc, argv, &option_all)) < 0)
		return (opts != -1);
	argc -= opts;
	argv += opts;
	if ((paths = ft_strsplit(getenv("PATH"), ':')) != NULL)
	{
		while (i < argc)
			err = (ft_search(argv[i++], paths, option_all) || err == 1);
		i = -1;
		while (paths[++i] != NULL)
			ft_strdel(&(paths[i]));
		ft_memdel((void *)(&paths));
	}
	return (err);
}
