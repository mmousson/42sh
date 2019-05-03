/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 21:18:38 by tduval            #+#    #+#             */
/*   Updated: 2019/05/03 23:31:14 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_files(char **files)
{
	int		i;

	i = 0;
	while (files && files[i])
	{
		ft_strdel(&files[i]);
		i++;
	}
	ft_memdel((void **)&files);
}

static char	**change_files(char **files, int f)
{
	int		i;

	i = -1;
	while (++i && files && files[i] && f == 1)
	{
		if (files[i] && ft_strcmp(files[i], ".") == 0)
		{
			ft_strdel(&files[i]);
			files[i] = ft_strdup("");
		}
	}
	while (++i && files && files[i] && f == 2)
	{
		if (files[i] && files[i + 1] && ft_strcmp(files[i + 1], "..") == 0)
		{
			ft_strdel(&files[i + 1]);
			files[i + 1] = ft_strdup("");
			ft_strdel(&files[i]);
			files[i] = ft_strdup("");
			i--;
		}
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
			res = ft_strjoin(tmp, ft_strdup(files[i]));
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
	return (res);
}

char	*get_pwd(char *cur)
{
	char	**files;
	char	*res;
	int		i;

	res = 0;
	i = 0;
	files = ft_strsplit(cur, '/');
	files = change_files(files, 1);
	res = get_res(files);
	free_files(files);
	files = ft_strsplit(cur, '/');
	files = change_files(files, 2);
	ft_strdel(&res);
	res = get_res(files);
	free_files(files);
	ft_putendl(res);
	return (res);
}
