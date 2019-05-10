/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 11:54:13 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/09 22:11:18 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

int				auto_isblank(void)
{
	int			i;

	i = g_env.p_size;
	while (g_env.line[i] && (g_env.line[i] == ' ' || g_env.line[i] == '\t'))
		i++;
	if (!g_env.line[i])
		return (1);
	return (0);
}

int				auto_checkroot(char *name, char *root)
{
	int			len;

	len = (int)ft_strlen(root);
	if (!len && name[0] == '.')
		return (0);
	if (ft_strncmp(name, root, len))
		return (0);
	return (1);
}

void				auto_calclen(void)
{
	t_lstword		*tmp;

	if (!g_data.lw->name)
		return ;
	tmp = g_data.lw;
	while (g_data.lw)
	{
		if (g_data.lw->len > g_data.lenmax)
			g_data.lenmax = g_data.lw->len;
		g_data.lw = g_data.lw->next;
		g_data.lenlst++;
	}
	g_data.lw = tmp;
	return ;
}
