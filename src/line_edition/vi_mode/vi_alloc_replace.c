/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_alloc_replace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 16:58:13 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/27 20:01:53 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

char			*vi_replace_str(char *str, int len)
{
	char		*fresh;
	int			lenstr;

	lenstr = (int)ft_strlen(str);
	if (!(fresh = ft_strnew(len)))
		sh_errorterm(TMALLOC);
	ft_strncpy(fresh, g_env.line, g_env.cm->pos);
	ft_strcpy(&(fresh[g_env.cm->pos]), str);
	ft_strcpy(&(fresh[g_env.cm->pos + lenstr]),
			&(g_env.line[g_env.cm->pos + lenstr]));
	ft_strdel(&(g_env.line));
	return (fresh);
}
