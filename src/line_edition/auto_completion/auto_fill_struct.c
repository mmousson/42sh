/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_fill_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 08:40:01 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/28 08:40:03 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

void				auto_filldata(void)
{
	char			*path;

	path = NULL;
	g_data.type = auto_getype();
	g_data.root = auto_getroot();
	g_data.var = auto_getvar();
	if (g_data.type == 3)
		g_data.com_option = auto_getcomoption();
	if (g_data.type)
		path = auto_getpath();
	else if (g_data.type == 0)
		path = getenv("PATH");
	if (!path || !(g_data.path = ft_strsplit(path, ':')))
		return ;
	if (g_data.type)
		ft_strdel(&path);
	g_data.lw = auto_new_lstword();
	g_data.spos = g_env.cm->pos;
}
