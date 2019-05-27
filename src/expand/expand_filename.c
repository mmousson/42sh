/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_filename.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 07:36:36 by akarasso          #+#    #+#             */
/*   Updated: 2019/05/27 19:23:18 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"
#include "libft.h"

int			expand_filename(char **path)
{
	char **files;
	char *new;

	if (!path || !(files = sh_glob(*path)))
		return (1);
	if (!(new = ft_strimplodef(files, ' ')))
	{
		ft_strtabdel(&files);
		return (1);
	}
	free(*path);
	*path = new;
	return (0);
}
