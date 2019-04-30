/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval </var/mail/tduval>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 08:37:24 by tduval            #+#    #+#             */
/*   Updated: 2019/04/30 02:48:35 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "cd.h"
#include "sh42.h"
#include "libft.h"

static void	free_list(char **list)
{
	int		i;

	i = 0;
	while (list && list[i])
	{
		ft_strdel(&list[i]);
		i++;
	}
	ft_memdel((void **)&list);
}

static char	*get_cur(char ***environ, char *dir, int *f)
{
	char	**list;
	char	*cdpath;
	char	*res;
	char	*tmp;
	int		i;

	i = 0;
	list = 0;
	res = 0;
	if (dir && (ft_strnequ(dir, "./", 2)
				|| ft_strnequ(dir, "../", 3)
				|| ft_strnequ(dir, "/", 1)))
	{
		*f = 1;
		return (ft_strdup(dir));
	}
	if ((cdpath = utility_get_env_var(environ, "CDPATH")))
	{
		if (!(list = ft_strsplit(cdpath, ':')))
			return (0);
		while (list[i])
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
				free_list(list);
				ft_putendl(res);
				return (res);
			}
			ft_strdel(&res);
			i++;
		}
	}
	*f = 1;
	i = 0;
	free_list(list);
	return (ft_strjoin("./", dir));
}

static int	changing_directory(char *dir[2], char ***env, char opts, int f)
{
	if (chdir(dir[1]) != -1)
	{
		ft_putendl(dir[1]);
		if ((opts & OPT_L) == 0)
			utility_add_entry_to_environ(env, "PWD", dir[1]);
		//else
			//TODO
		ft_strdel(&dir[1]);
		return (0);
	}
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd("no such file or directory: ", 2);
	ft_putendl_fd(f ? dir[0] : dir[1], 2);
	ft_strdel(&dir[1]);
	return (1);
}

int			cd(int argc, char **argv, char ***env)

{
	char	opts;
	char	*tmp;
	char	*dir[2];
	int		f;

	opts = 0;
	dir[0] = NULL;
	dir[1] = NULL;
	f = 0;
	if ((opts = cd_get_opts(argv, &dir[0])) == -1)
	{
		ft_putendl_fd("cd: error: too many arguments.", 2);
		return (1);
	}
	if (ft_strequ(dir[0], "-"))
	{
		dir[1] = ft_strdup(utility_get_env_var(env, "OLDPWD"));
		if (access(dir[1], F_OK) == 0)
			ft_putendl(dir[1]);
		return (changing_directory(dir, env, opts, f));
	}
	if (dir[0] == NULL)
	{
		if (!(dir[0] = utility_get_env_var(env, "HOME")))
			return (1);
	}
	if (!(dir[1] = get_cur(env, dir[0], &f)))
		return (1);
	if (dir[1][0] != '/')
	{
		tmp = ft_strdup(dir[1]);
		dir[1] = ft_strjoin(utility_get_env_var(env, "PWD"), "/");
		dir[1] = ft_strjoin(dir[1], tmp);
		ft_strdel(&tmp);
	}
	return (changing_directory(dir, env, opts, f));
}

int		main(int ac, char **av, char **env)
{
	char	**cpy;
	int		i;

	i = 0;
	cpy = utility_duplicate_environ(env);
	cd(ac, av, &cpy);
	ft_putendl("\n --------------------------------- \n");
	while (cpy[i])
	{
		ft_putendl(cpy[i]);
		ft_strdel(&(cpy[i]));
		i++;
	}
	ft_memdel((void **)&cpy);
	return (0);
}
