/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_search_utility.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 15:21:03 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/16 15:15:53 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "libft.h"
#include "sh42.h"

/*
**	In case of a matching entry in the currently searched directory, we
**	generate the absolute path of the binary with:
**	The directory name in which it has been found, on which we append a '/'
**	on which we append the utility name
**
**	Arguments:
**	dir -> The directory name containing the binary we are looking for
**	utility -> The binary name we are looking for
**
**	Return Value:
**	NULL -> A malloc error occured, the program should be exited promptly
**	NON-NULL -> The full path of the target binary
*/

static char	*generate_path(char *dir, char *utility)
{
	char	*tmp;
	char	*result;

	if ((tmp = ft_strjoin(dir, "/")) == NULL)
	{
		ft_putendl_fd("42sh: Internal malloc error", STDERR_FILENO);
		return (NULL);
	}
	if ((result = ft_strjoin(tmp, utility)) == NULL)
		ft_putendl_fd("42sh: Internal malloc error", STDERR_FILENO);
	ft_strdel(&tmp);
	return (result);
}

/*
**	This function is a subloop of the function defined below
**	It will search through the entire directory 'dir_name' for an entry
**	with a name matching 'utility'
**
**	Arguments:
**	dir_name -> The string representing the currently searched directory's name
**	utility -> The name of the binary we are looking for
**	dir -> A DIR pointer to the directory that has been successfully opened
**
**	Return Value:
**	NULL -> The binary doesn't exist in the specified directory
**	NON-NULL -> The binary has been found and its full path is returned
*/

static char	*search_directory(char *dir_name, char *utility, DIR *dir)
{
	char			*result;
	struct dirent	*sd;

	result = NULL;
	while ((sd = readdir(dir)) != NULL)
	{
		if (ft_strequ(sd->d_name, utility))
		{
			result = generate_path(dir_name, utility);
			break ;
		}
	}
	closedir(dir);
	return (result);
}

/*
**	This utility function searches all the folders specified in PATH for a
**	binary matching the name 'name'
**	If it founds one, it will return a freshly allocated pointer to a string
**	holding the full path to the binary
**	If the binary doesn't exist in PATH, it will return (NULL)
**
**	Arguments:
**	env -> The shell's current environment
**	name -> The name of the binary to search for (e.g: ls)
**
**	Return Value:
**	NULL -> The specified binary doesn't exist in PATH
**	NON-NULL -> The binary was found in PATH and its full PATH was returned
**	in a newly allocated buffer
*/

char		*utility_search(char **env, char *name, int val_to_set_hash_hits)
{
	int		i;
	DIR		*dir;
	char	*path;
	char	**paths;
	char	*result;

	i = -1;
	result = NULL;
	paths = NULL;
	path = utility_get_var("PATH", env);
	if (path != NULL && (paths = ft_strsplit(path, ':')) == NULL)
		ft_putendl_fd("42sh: Internal malloc error", STDERR_FILENO);
	while (paths && paths[++i] != NULL)
	{
		if (result == NULL && (dir = opendir(paths[i])) != NULL)
			result = search_directory(paths[i], name, dir);
		ft_strdel(&(paths[i]));
	}
	ft_strdel(&path);
	ft_memdel((void *)(&paths));
	if (val_to_set_hash_hits > -1 && result != NULL)
		hash_add_entry(hash_string(name), name, result, val_to_set_hash_hits);
	return (result);
}
