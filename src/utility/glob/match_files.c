/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 08:33:56 by hben-yah          #+#    #+#             */
/*   Updated: 2019/07/04 14:06:53 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"
#include "libft.h"

int			match_files(t_glob *gl)
{
	char	**files;
	char	*path;

	if (!(files = get_files_to_match(gl)))
		return (1);
	if (!(gl->lexer = globlexnew(0)))
	{
		ft_strtabdel(&files);
		return (1);
	}
	if (!tokenize(gl))
	{
		if (gl->lexer->first && check_matching_files(gl, files) == 0)
		{
			if (!(path = ft_strjoin(gl->root, gl->expr))
				|| !ft_strtabadd(&gl->res, path))
				return (1);
		}
	}
	globlexdel(&gl->lexer);
	ft_strtabdel(&files);
	return (0);
}
