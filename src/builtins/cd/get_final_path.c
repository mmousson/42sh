/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_final_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 19:33:08 by hben-yah          #+#    #+#             */
/*   Updated: 2019/06/13 12:08:00 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"
#include "libft.h"

static char		*get_complete_path(char *parent, char *name)
{
	char	*tmp;
	char	*result;

	if (parent == NULL || name == NULL)
		return (NULL);
	if (name[0] == '/')
		return (name);
	if (name[0] == '.' && name[1] == '/')
	{
		if (!(tmp = ft_strdup(&name[2])))
			return (NULL);
		ft_strdel(&name);
		name = tmp;
	}
	if (parent[ft_strlen(parent) - 1] == '/')
		tmp = ft_strdup(parent);
	else
		tmp = ft_strjoin(parent, "/");
	if (!tmp)
		return (NULL);
	if (!(result = ft_strjoin(tmp, name)))
		return (NULL);
	ft_strdel(&tmp);
	return (result);
}

static void		clean_absolute_path(char **path)
{
	char	**pwd_tab;
	char	*str;

	if ((*path)[0] == '/' && (*path)[1] != '.')
	{
		if (!(pwd_tab = ft_strsplit(*path, '/')))
			return ;
		if (!(str = ft_strjointab(pwd_tab, '/')))
		{
			ft_strtabdel(&pwd_tab);
			return ;
		}
		ft_strtabdel(&pwd_tab);
		ft_strdel(path);
		*path = ft_strdup(str);
		ft_strdel(&str);
	}
}

static char		*check_cdpath(char *cdpath, char *dir)
{
	char	**list;
	char	*res;
	int		i;

	i = 0;
	list = ft_strsplit(cdpath, ':');
	while (list && list[i])
	{
		if (list[i][ft_strlen(list[i]) - 1] == '/')
			res = ft_strjoin(list[i], dir);
		else
			res = ft_strjoin3fs(list[i], "/", dir, 0);
		if (access(res, F_OK) == 0)
		{
			ft_strtabdel(&list);
			ft_putendl_fd(res, 1);
			return (res);
		}
		ft_strdel(&res);
		++i;
	}
	ft_strtabdel(&list);
	return (NULL);
}

char			*get_final_path(char **path, char **cdenv)
{
	char			**arg_tab;
	char			**pwd_tab;
	char			*str;

	if (!cdenv[2])
		cdenv[2] = getcwd(NULL, 0);
	clean_absolute_path(path);
	if (cdenv[3] && (*path)[0] != '/' && !ft_strnequ(*path, "./", 2)
		&& !ft_strnequ(*path, "../", 3)
		&& (str = check_cdpath(cdenv[3], *path)))
		return (str);
	if ((*path)[0] == '/' && (*path)[1] != '.')
		return (ft_strdup(get_complete_path(cdenv[2], *path)));
	if (!(arg_tab = ft_strsplit(*path, '/'))
		|| !(pwd_tab = ft_strsplit(cdenv[2], '/'))
		|| !build_pwd_tab(&arg_tab, &pwd_tab, ft_strtablen(pwd_tab)))
	{
		ft_strtabdel2(&arg_tab, &pwd_tab);
		return (NULL);
	}
	str = ft_strjointab(pwd_tab, '/');
	ft_strtabdel2(&arg_tab, &pwd_tab);
	return (str);
}
