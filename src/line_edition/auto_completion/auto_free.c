/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 13:39:41 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/25 14:33:05 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

void						auto_free_lstword(t_lstword *lw)
{
	if (!lw)
		return ;
	if (lw->next)
		auto_free_lstword(lw->next);
	if (lw->name)
	{
		ft_strdel(&(lw->name->name));
		ft_strdel(&(lw->name->desc));
		ft_memdel((void**)&lw->name);
	}
	ft_memdel((void**)&lw);
}

void						auto_free(void)
{
	auto_free_lstword(g_data.lw);
	ft_del_words_tables(&g_data.path);
	ft_strdel(&g_data.root);
	ft_strdel(&g_data.var);
	ft_strdel(&g_data.com_option);
	ft_bzero(&g_data, sizeof(t_autodata));
	g_data.lw = NULL;
}
