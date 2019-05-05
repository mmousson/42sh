/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 02:51:04 by tduval            #+#    #+#             */
/*   Updated: 2019/05/06 01:48:28 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "cd.h"
#include "sh42.h"
#include "libft.h"

static char	*check_cdpath(char *cdpath, char *dir, char *res, int i)
{
	char	*tmp;
	char	**list;

	list = ft_strsplit(cdpath, ':');
	while (list && list[i])
	{
		if (list[i][ft_strlen(list[i]) - 1] == '/')
			res = ft_strjoin(list[i], dir);
		else
		{
			tmp = ft_strjoin(list[i], "/");
			res = ft_strjoin(tmp, dir);
			ft_strdel(&tmp);
		}
		if (access(res, F_OK) == 0)
		{
			cd_free_files(list);
			return (res);
		}
		ft_strdel(&res);
		i++;
	}
	cd_free_files(list);
	return (res);
}

static char	*get_cur(char ***environ, char *dir, int *f)
{
	char	*cdpath;
	char	*res;
	char	*tmp;

	res = 0;
	if (dir && (ft_strnequ(dir, "./", 2) || ft_strnequ(dir, "../", 3)
			|| ft_strnequ(dir, "/", 1)))
	{
		*f = 1;
		return (ft_strdup(dir));
	}
	if ((cdpath = utility_get_env_var(environ, "CDPATH")))
	{
		if ((res = check_cdpath(cdpath, dir, NULL, 0)) != NULL)
		{
			tmp = cd_get_pwd(res);
			ft_putendl(tmp);
			ft_strdel(&tmp);
			return (res);
		}
	}
	*f = 1;
	return (ft_strjoin("./", dir));
}

static int	first_part(char **argv, char *opts, char *dir[2], char ***env)
{
	if ((*opts = cd_get_opts(argv, &dir[0])) == -1)
	{
		ft_putendl_fd("cd: error: too many arguments.", 2);
		return (1);
	}
	if (ft_strequ(dir[0], "-"))
	{
		dir[1] = ft_strdup(utility_get_env_var(env, "OLDPWD"));
		if (access(dir[1], F_OK) == 0)
			ft_putendl(dir[1]);
		return (cd_changing_directory(dir, env, *opts, 0));
	}
	if (dir[0] == NULL)
	{
		if (!(dir[0] = utility_get_env_var(env, "HOME")))
			return (1);
	}
	return (2);
}

static char	*get_dir_one(char *pwd)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(pwd, "/");
	res = ft_strjoin("/", tmp);
	ft_strdel(&tmp);
	return (res);
}

int			blt_cd(int argc, char **argv, char ***env)
{
	char	pwd[4096];
	char	*tmp[2];
	char	*dir[2];
	char	opts;
	int		f;

	f = 0;
	if (argc && (f = first_part(argv, &opts, dir, env)) != 2)
		return (f);
	dir[1] = get_cur(env, dir[0], &f);
	if (dir[1] && dir[1][0] != '/')
	{
		ft_strdel(&dir[1]);
		tmp[0] = ft_strdup(dir[0]);
		if (opts == OPT_P
				&& readlink(utility_get_env_var(env, "PWD"), pwd, 4096) != -1)
			dir[1] = get_dir_one(pwd);
		else
			dir[1] = ft_strjoin(utility_get_env_var(env, "PWD"), "/");
		tmp[1] = ft_strjoin(dir[1], tmp[0]);
		ft_strdel(&dir[1]);
		dir[1] = tmp[1];
		ft_strdel(&tmp[0]);
	}
	return (dir[1] ? cd_changing_directory(dir, env, opts, f) : 1);
}
