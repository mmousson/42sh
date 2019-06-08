/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 08:04:24 by hben-yah          #+#    #+#             */
/*   Updated: 2019/06/08 19:34:02 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "glob.h"
#include "libft.h"

static int
	check_repertory(char ***files, char **path, struct dirent *ent, int depth)
{
	if (!ft_strequ(ent->d_name, ".") && !ft_strequ(ent->d_name, "..")
		&& ent->d_type & DT_DIR
		&& (!(*path = ft_strjoinfs(*path, "/", FT_ARG1))
		|| read_directory(files, *path, depth - 1)))
	{
		ft_strdel(path);
		return (1);
	}
	return (0);
}

static int
	check_entry(char ***files, DIR *dir, char *path, int depth)
{
	struct dirent	*entry;
	char			*ptr;

	while ((entry = readdir(dir)))
	{
		if (!(ptr = ft_strjoin(path, entry->d_name)))
			return (1);
		if (depth > 0)
		{
			if (check_repertory(files, &ptr, entry, depth))
				return (1);
			ft_strdel(&ptr);
		}
		else if (!ft_strtabadd(files, ptr))
		{
			free(ptr);
			return (1);
		}
	}
	return (0);
}

int
	read_directory(char ***files, char *path, int depth)
{
	DIR		*dir;
	int		ret;

	ret = 0;
	if ((dir = opendir(!*path ? "./" : path)))
	{
		if ((ret = check_entry(files, dir, !*path ? "" : path, depth)))
			ft_strtabdel(files);
		closedir(dir);
	}
	return (ret);
}

char
	**get_files_to_match(t_glob *gl)
{
	char	**files;

	files = NULL;
	gl->depth = get_path_depth(gl->expr);
	if (read_directory(&files, gl->root, gl->depth))
	{
		ft_strtabdel(&files);
		return (NULL);
	}
	return (files);
}
