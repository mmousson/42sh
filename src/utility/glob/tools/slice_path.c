/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slice_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 18:01:12 by hben-yah          #+#    #+#             */
/*   Updated: 2019/06/05 14:46:55 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"
#include "libft.h"

static char	*walk_next_complete_namespace(char *s)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == '\\')
			++s;
		else if (*s == '/')
			return (s + 1);
		else if (*s == '"' || *s == '\''
				|| *s == '*' || *s == '?'
				|| *s == '[')
			break ;
		if (*s)
			++s;
	}
	return (NULL);
}

int			slice_path(t_glob *gl, char *path)
{
	char *delim;
	char *tmp;

	delim = path;
	tmp = path;
	while (*tmp && (tmp = walk_next_complete_namespace(tmp)))
		delim = tmp;
	gl->root_len = delim - path;
	if (!(gl->root = ft_strsub(path, 0, gl->root_len)))
		return (1);
	if (!(gl->expr = ft_strdup(delim)))
	{
		ft_strdel(&gl->root);
		return (1);
	}
	return (0);
}
