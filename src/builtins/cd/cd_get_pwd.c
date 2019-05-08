/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_get_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 21:18:38 by tduval            #+#    #+#             */
/*   Updated: 2019/05/08 14:10:06 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"
#include "libft.h"

static char	**delete_last(char **files, int i)
{
	while (i && ft_strequ(files[i], ""))
		i--;
	ft_strdel(&files[i]);
	files[i] = ft_strdup("");
	return (files);
}

static char	**change_files(char **files, int f)
{
	int		i;

	i = 0;
	while (files && files[i] && f == 1)
	{
		if (files[i] && ft_strcmp(files[i], ".") == 0)
		{
			ft_strdel(&files[i]);
			files[i] = ft_strdup("");
		}
		i++;
	}
	while (files && files[i] && f == 2)
	{
		if (ft_strcmp(files[i], "..") == 0)
		{
			ft_strdel(&files[i]);
			files[i] = ft_strdup("");
			if (i)
				files = delete_last(files, i);
			i = -1;
		}
		i++;
	}
	return (files);
}

static char	*get_res(char **files)
{
	char	*res;
	char	*tmp;
	int		i;

	i = 0;
	res = 0;
	while (files && files[i])
	{
		if (res == 0 && ft_strcmp(files[i], ""))
		{
			tmp = ft_strdup("/");
			res = ft_strjoin(tmp, files[i]);
			ft_strdel(&tmp);
		}
		else if (ft_strcmp(files[i], ""))
		{
			tmp = ft_strjoin(res, "/");
			ft_strdel(&res);
			res = ft_strjoin(tmp, files[i]);
			ft_strdel(&tmp);
		}
		i++;
	}
	return (res ? res : ft_strdup("/"));
}

char		*cd_get_pwd(char *cur)
{
	char	**files;
	char	*res;

	files = NULL;
	res = NULL;
	files = ft_strsplit(cur, '/');
	files = change_files(files, 1);
	res = get_res(files);
	cd_free_files(files);
	files = ft_strsplit(res, '/');
	files = change_files(files, 2);
	ft_strdel(&res);
	res = get_res(files);
	cd_free_files(files);
	return (res);
}
