/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 00:07:27 by oboutrol          #+#    #+#             */
/*   Updated: 2019/04/03 20:25:03 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexpars.h"
#include "libft.h"
#include <stdlib.h>

int				ft_point_slash(char *name, char **path)
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

int				ft_path(char *name, char **path, char **arge)
{
	char		**ways;
	int			k;
	char		*abs_name;
	int			ret;

	if (!(ways = ft_split_path(arge)))
		return (0);
	k = -1;
	if ((ret = ft_point_slash(name, path)) == 1 || ret == 0)
		return (ret);
	while (ways[++k])
	{
		abs_name = ft_strjoin(ways[k], name);
		if (is_exec(abs_name))
		{
			*path = abs_name;
			if (ways)
				ft_del_words_tables(&ways);
			return (1);
		}
		free(abs_name);
	}
	if (ways)
		ft_del_words_tables(&ways);
	return (0);
}
