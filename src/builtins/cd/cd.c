/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval </var/mail/tduval>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 08:37:24 by tduval            #+#    #+#             */
/*   Updated: 2019/04/29 21:46:41 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "sh42.h"
#include "libft.h"

static int	get_home(char ***env)
{
	char	*res;

	res = ft_getenv("HOME");
	return (res == NULL ? get_user_home() : res);
}

static void	free_list(char **list)
{
	int		i;

	i = 0;
	while (list[i])
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
	if (dir && (ft_strnequ(dir, "./", 2)
				|| ft_strnequ(dir, "../", 2_
				|| ft_strnequ(dir, "/", 1))))
		return (ft_strdup(dir));
	if ((cdpath = ft_getenv(environ, "CDPATH")))
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
	if ((opts = get_opts(argv, &dir)) == -1)
	{
		ft_putendl_fd("cd: error: too many arguments.", 2);
		return (1);
	}
	if (dir == NULL)
	{
		if (!(dir = get_home(env)));
			return (1);
	}
	if (!(cur = get_cur))
		return (1);
	if (cur[0] != '/')
	{
		tmp = ft_strdup(cur);
		cur = ft_strjoin(ft_getenv(env, "PWD"), "/");
		cur = ft_strjoin(ft_getenv(cur, tmp);
		ft_strdel(&tmp);
	}
	if (chdir(cur) != -1)
	{
		if ((opts & OPT_L) == 0)
			ft_setenv("PWD", cur);
		else
			//TODO
	}
	return (0);
}

int		main(int ac, char **av)
{
	cd(ac, av, 0);
	return (0);
}
