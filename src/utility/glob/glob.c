/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 07:36:36 by hben-yah          #+#    #+#             */
/*   Updated: 2019/06/06 13:53:58 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"
#include "libft.h"

void	init_glob(t_glob *gl)
{
	ft_bzero(gl, sizeof(t_glob));
}

void	reset_glob(t_glob *gl)
{
	ft_strdel(&gl->root);
	ft_strdel(&gl->expr);
}

char	**sh_glob(char *path)
{
	t_glob	gl;
	char	**files;

	if (!path)
		return (NULL);
	init_glob(&gl);
	if (slice_path(&gl, path))
		return (NULL);
	if (match_files(&gl))
	{
		reset_glob(&gl);
		return (NULL);
	}
	files = gl.res;
	reset_glob(&gl);
	return (files);
}
