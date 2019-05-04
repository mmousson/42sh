/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_classic.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 06:52:44 by mmousson          #+#    #+#             */
/*   Updated: 2019/05/04 12:19:13 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "line_edition.h"

/*
**	Merges both the 'usr' and 'path' strings, allocating enough space for
**	-> The two strings
**	-> The two brackets '[' AND ']' at the beginning and the end of the result
**	-> The separator ':' between 'usr' AND 'path'
**	-> The NULL terminator
*/

static int		ft_merge(char *usr, char *path, int error, char **env)
{
	int	add;

	add = 0;
	ft_putchar(' ');
	ft_putstr(USER_FONT);
	ft_putstr(usr);
	ft_putstr(BANNER_START);
	ft_putstr("\xEE\x82\xB0 ");
	ft_putstr(error ? "\033[0;38;2;255;100;100;48;2;50;50;50m"
		: "\033[0;38;2;140;140;140;48;2;50;50;50m");
	prompt_format_path(path);
	ft_putchar(' ');
	prompt_git_branch(error, env);
	return (ft_strlen(usr) + ft_strlen(path) + 15 + add);
}

static char		*ft_trim_path(char *original)
{
	int		i;
	int		folder_count;
	char	*res;

	if (original == NULL)
	{
		res = ft_strdup("!!PWD UNDEFINED!!");
		if (res == NULL)
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
**	Then it returns the length of the string printed on screen
*/

int				line_write_prompt(char ***environ, int error)
{
	char	*usr;
	char	*path;
	int		ret;

	path = ft_trim_path(getenv("PWD")); //getenv -> to get_env_var
	if ((usr = ft_strdup(getenv("USER"))) == NULL) //getenv -> to get_env_var
		usr = ft_strdup("!!USER UNDEFINED!!");
	if (usr == NULL || path == NULL)
	{
		ft_putendl_fd("Internal Malloc Error", STDERR_FILENO);
		return (-1);
	}
	if ((ret = ft_merge(usr, path, error, *environ)) == 0)
	{
		ft_putendl_fd("Internal Malloc Error", STDERR_FILENO);
		ret = -1;
	}
	ft_strdel(&usr);
	ft_strdel(&path);
	if (ret == -1)
	{
		ft_putstr("$> ");
		ret = 3;
	}
	return (ret);
}

int				main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;

	ft_putendl("\n");
	line_write_prompt(&env, argc > 1);
	ft_putendl("\n");
	return(0);
}
