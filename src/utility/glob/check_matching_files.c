/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_matching_files.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 08:35:55 by hben-yah          #+#    #+#             */
/*   Updated: 2019/06/04 17:30:14 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"
#include "libft.h"

int		is_file_matching_pattern(t_globtok *tok, char *path)
{
	t_chr_token	*data;

	if (!tok)
		return (!*path);
	if (tok && tok->data)
	{
		data = (t_chr_token *)tok->data;
		if (data->type == GLO_STAR)
			return (is_matching_asterisk(tok, path));
		if (data->type == GLO_QUEST)
			return (is_matching_question(tok, path));
		if (data->type == GLO_CONST)
			return (is_matching_const(tok, tok->data, path));
		if (data->type == GLO_RANGE)
			return (is_matching_range(tok, tok->data, path));
		if (data->type == GLO_SEPAR)
		{
			if (!*path)
				return (1);
			if (*path == '/')
				return (is_file_matching_pattern(tok->next, path + 1));
		}
	}
	return (0);
}

int		check_matching_files(t_glob *gl, char **files)
{
	char	*path;
	int		pos;

	pos = 0;
	if (files)
		while (*files)
		{
			if (is_file_matching_pattern(gl->lexer->first,
												*files + gl->root_len))
			{
				if (!(path = ft_strdup(*files))
					|| !ft_strtabadd(&gl->res, path))
				{
					while (pos)
						ft_strdel(&gl->res[pos--]);
					return (0);
				}
				++pos;
			}
			++files;
		}
	return (pos);
}
