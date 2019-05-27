/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_depth.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 18:01:03 by hben-yah          #+#    #+#             */
/*   Updated: 2019/05/27 19:20:16 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"

int		get_path_depth(char *path)
{
	int depth;

	depth = 0;
	while (*path)
	{
		if (*path == '[')
			walk_range(&path);
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
