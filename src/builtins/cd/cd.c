/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval </var/mail/tduval>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 08:37:24 by tduval            #+#    #+#             */
/*   Updated: 2019/04/29 23:02:07 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "cd.h"
#include "sh42.h"
#include "libft.h"

static char	*get_home(char ***env)
{
	char	*res;

	res = utility_get_env_var(env, "HOME");
	return (res == NULL ? utility_get_user_home() : res);
}

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

static char	*get_cur(char ***environ, char *dir)
{
	char	**list;
	char	*cdpath;
	char	*res;
	int		i;

	i = 0;
	list = 0;
	if (dir && (ft_strnequ(dir, "./", 2)
				|| ft_strnequ(dir, "../", 2)
				|| ft_strnequ(dir, "/", 1)))
		return (ft_strdup(dir));
	if ((cdpath = utility_get_env_var(environ, "CDPATH")))
	{
		if (!(list = ft_strsplit(cdpath, ':')))
		{
			ft_strdel(&cdpath);
			return (0);
		}
		while (list[i])
		{
			if (access(list[i], F_OK) == 0)
			{
				res = ft_strjoin(list[i], dir);
				free_list(list);
				ft_strdel(&cdpath);
				return (res);
			}
			i++;
		}
	}
	i = 0;
	free_list(list);
	ft_strdel(&cdpath);
	return (ft_strjoin("./", dir));
}

int			cd(int argc, char **argv, char ***env)

{
	char	opts;
	char	*tmp;
	char	*dir;
	char	*cur;

	dir = NULL;
	cur = NULL;
	if ((opts = cd_get_opts(argv, &dir)) == -1)
	{
		ft_putendl_fd("cd: error: too many arguments.", 2);
		return (1);
	}
	if (dir == NULL)
	{
		if (!(dir = get_home(env)))
			return (1);
	}
	if (!(cur = get_cur(env, dir)))
		return (1);
	if (cur[0] != '/')
	{
		tmp = ft_strdup(cur);
		cur = ft_strjoin(utility_get_env_var(env, "PWD"), "/");
		cur = ft_strjoin(cur, tmp);
		ft_strdel(&tmp);
	}
	if (chdir(cur) != -1)
	{
		ft_putendl(cur);
		if ((opts & OPT_L) == 0)
			utility_add_entry_to_environ(env, "PWD", cur);
		//else
			//TODO
	}
	return (0);
}

int		main(int ac, char **av)
{
	cd(ac, av, 0);
	return (0);
}
