/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_classic.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 06:52:44 by mmousson          #+#    #+#             */
/*   Updated: 2019/05/07 06:24:24 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "libft.h"
#include "prompt.h"

/*
**	Puts a Powerline arrow with a space and returns its size (2)
*/

int				put_arrow(char *arrow)
{
	ft_putstr_fd(arrow, 1);
	return (2);
}

/*
**	Merges both the 'usr' and 'path' strings, allocating enough space for:
**	-> The two strings
**	-> The two brackets '[' AND ']' at the beginning and the end of the result
**	-> The separator ':' between 'usr' AND 'path'
**	-> The NULL terminator
**	Plus, informations about the current git repository, if any
**	will be displayed
**
**	Arguments:
**	usr -> The string containing the name of the current user
**	path -> The string containing the path to the current directory, trimmed
**		by the function 'ft_trim_path' defined below
**	error -> Boolean variable telling us whether or not an error occured
**		and if so, the path will be displayed in red
**	env -> The shell's current environment definiton
*/

static int		ft_merge(char *usr, char *path, int error, char **env)
{
	int	add;
	int	ret;

	add = 0;
	ft_putchar(' ');
	ft_putstr(USER_FONT);
	ret = write(1, usr, ft_strlen(usr)) + 2;
	ret += put_arrow(BANNER_START""BANNER_ARROW);
	ft_putstr(error ? "\033[0;38;2;255;100;100;48;2;50;50;50m"
		: "\033[0;38;2;140;140;140;48;2;50;50;50m");
	ret += prompt_format_path(path);
	ret += write(1, " ", 1);
	ret += prompt_git_branch(env);
	ret += write(1, " ", 1);
	return (ret);
}

/*
**	This function trims a path so it can show up to 3 folders in depth
**	If the 'orginal' arguments is NULL, then it means that the environment
**	variable 'PWD' is unset and in this case we display the current path as
**	'!!!PWD UNDEFINED!!!'
**
**	Arguments:
**	original -> The full path to the current directory that needs to be trmmed
**
**	Return Value:
**	NULL -> A memory allocation occured, the program should exit promptly
**	NON-NULL -> The formatted path to display in the prompt
*/

static char		*ft_trim_path(char *original)
{
	int		i;
	int		folder_count;
	char	*res;

	if (original == NULL)
	{
		if ((res = ft_strdup("!!PWD UNDEFINED!!")) == NULL)
			ft_putendl_fd("Internal Malloc Error", STDERR_FILENO);
		return (res);
	}
	i = 0;
	folder_count = 1;
	while (original[i] != '\0')
		i++;
	while (--i >= 0 && folder_count <= 2)
		if (original[i] == '/')
			folder_count++;
	if (i > 0)
		res = ft_strjoin("...", original + i + 1);
	else
		res = ft_strdup(original);
	if (res == NULL)
		ft_putendl_fd("Internal Malloc Error", STDERR_FILENO);
	return (res);
}

/*
**	This function write a prompt invite on screen, with the following
**	informations: USER, PATH TO CURRENT DIR (with 2 folders max. depth)
**	And the number of additions and deletions in the current
**	Git repositor, if any
**	Then it returns the length of the string printed on screen
**
**	Arguments:
**	environ -> The shell's current environment definiton
**	error -> Boolean variable telling us whether or not an error occured
**		and if so, the path will be displayed in red
**
**	Return Value:
**	The number of columns the prompt takes on screen. This value will then
**		be used as an offset for 'line_edition' engine
*/

int				line_write_prompt(char ***environ, int error)
{
	char	*usr;
	char	*path;
	int		ret;

	if ((path = ft_trim_path(ft_get_env_var(environ, "PWD"))) == NULL
		|| (usr = utility_get_effective_user_name()) == NULL)
	{
		ft_putendl_fd("Internal Malloc Error", STDERR_FILENO);
		ret = -1;
	}
	else if ((ret = ft_merge(usr, path, error, *environ)) == 0)
	{
		ft_putendl_fd("Internal Malloc Error", STDERR_FILENO);
		ret = -1;
	}
	if (ret == -1)
	{
		ft_putstr("$> ");
		ret = 3;
	}
	ft_strdel(&usr);
	ft_strdel(&path);
	return (ret);
}
