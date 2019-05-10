/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 00:07:27 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/04 16:38:41 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"
#include "libft.h"
#include <stdlib.h>

static int		ft_point_slash(char *name, char **path)
{
	if (!ft_strncmp(name, "./", 2))
	{
		if (is_exec(name))
		{
			if (!(*path = ft_strdup(name)))
				return (0);
			return (1);
		}
		return (0);
	}
	return (2);
}

static int		check_this_path(char **ways, char *name, int k, char **path)
{
	char		*abs_name;

	abs_name = ft_strjoin(ways[k], name);
	if (is_exec(abs_name))
	{
		*path = abs_name;
		if (ways)
			ft_del_words_tables(&ways);
		return (1);
	}
	free(abs_name);
	return (0);
}

int				ft_path(char *name, char **path, char **arge)
{
	char		**ways;
	int			k;
	int			ret;

	k = -1;
	if ((ret = ft_point_slash(name, path)) == 1 || ret == 0)
		return (ret);
	if (is_exec(name))
	{
		*path = ft_strdup(name);
		return (1);
	}
	if (!(ways = ft_split_path(arge)))
		return (0);
	while (ways[++k])
	{
		if (check_this_path(ways, name, k, path))
			return (1);
	}
	if (ways)
		ft_del_words_tables(&ways);
	return (0);
}
