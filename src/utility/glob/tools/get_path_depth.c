/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_depth.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 18:01:03 by hben-yah          #+#    #+#             */
/*   Updated: 2019/06/07 16:54:48 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"

int		get_path_depth(char *path)
{
	int depth;
	// mettre un systeme pour qu'ICI on puisse savoir si caché ou pas caché 

	depth = 0;
	while (*path)
	{
		if (*path == '[' && walk_range(&path))
			++path;
		else
		{
			if (*path == '/')
			{
				while (*(path + 1) == '/')
					++path;
				if (*(path + 1))
					++depth;
			}
			++path;
		}
	}
	return (depth);
}
