/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_pwd_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 19:34:08 by hben-yah          #+#    #+#             */
/*   Updated: 2019/05/29 14:14:01 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "sh42.h"
#include "cd.h"
#include "libft.h"

int			check_path_errors(char *path)
{
	struct stat st;

	if ((stat(path, &st)) < 0)
	{
		ft_putstr3_fd(""SH_NAME": cd: no such file or directory: ",
																path, "\n", 2);
		return (0);
	}
	else
	{
		if (!S_ISDIR(st.st_mode))
		{
			ft_putstr3_fd(""SH_NAME": cd: not a directory: ", path, "\n", 2);
			return (0);
		}
	}
	return (1);
}

static int	ft_realloc_addend_tab(char ***arr, char *elem)
{
	int		i;
	char	**tmp;

	if (*arr == NULL || !elem)
		return (0);
	i = -1;
	while ((*arr)[++i])
		;
	if (!(tmp = ft_memalloc((i + 2) * sizeof(char *))))
		return (0);
	i = -1;
	while ((*arr)[++i])
		if (!(tmp[i] = ft_strdup((*arr)[i])))
			return (0);
	if (!(tmp[i] = ft_strdup(elem)))
		return (0);
	tmp[i + 1] = NULL;
	ft_strtabdel(arr);
	*arr = tmp;
	return (1);
}

static int	dotdot_case(char ***pwd_tab, int *pwd_tab_len)
{
	if (*pwd_tab_len <= 0)
		return (1);
	ft_strdel(&(*pwd_tab)[(*pwd_tab_len) - 1]);
	(*pwd_tab)[(*pwd_tab_len) - 1] = NULL;
	if (!(*pwd_tab)[0])
	{
		if (!(ft_realloc_addend_tab(pwd_tab, "")))
			return (0);
	}
	else
		(*pwd_tab_len)--;
	return (1);
}

static int	check_validity_path(char ***pwd_tab)
{
	char *tmp;

	if (!(tmp = ft_strjointab(*pwd_tab, '/')))
		return (0);
	if (!check_path_errors(tmp))
	{
		ft_strdel(&tmp);
		return (0);
	}
	ft_strdel(&tmp);
	return (1);
}

int			build_pwd_tab(char ***arg_tab, char ***pwd_tab, int pwd_tab_len)
{
	int		i;

	i = -1;
	while ((*arg_tab)[++i])
	{
		if (ft_strcmp((*arg_tab)[i], "..") == 0)
		{
			if (!dotdot_case(pwd_tab, &pwd_tab_len))
				return (0);
		}
		else if (ft_strcmp((*arg_tab)[i], ".") == 0)
			continue;
		else
		{
			if (!(ft_realloc_addend_tab(pwd_tab, (*arg_tab)[i])))
				return (0);
			pwd_tab_len++;
		}
		if (!check_validity_path(pwd_tab))
			return (0);
	}
	return (1);
}
