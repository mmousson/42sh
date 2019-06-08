/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 07:36:36 by hben-yah          #+#    #+#             */
/*   Updated: 2019/06/08 18:25:35 by hben-yah         ###   ########.fr       */
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

// int		check_is_pattern(char *s)
// {
// 	int search_quote;

// 	search_quote = 0;
// 	while (*s)
// 	{
// 		if (*s == '\\')
// 			++s;
// 		else if (*s == '\'')
// 			search_quote = !search_quote;
// 		else if (!search_quote && (*s == '*' || *s == '?' || *s == '['))
// 			return (1);
// 		if (*s)
// 			++s;
// 	}
// 	return (0);
// }

char	**sh_glob(char *path)
{
	t_glob	gl;
	char	**files;

	if (!path)
		return (NULL);
	// if (check_is_pattern(path));
	// 	return (ft_strdup(path));
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
