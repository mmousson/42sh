/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 11:54:13 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/28 18:36:59 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

int				auto_lenrootwbs(void)
{
	int			i;
	int			count;

	if (g_data.type == 3)
		return (1);
	i = g_env.cm->pos - 1;
	count = 0;
	while (i - g_env.p_size + 1
			&& auto_ischar(g_env.line[i], g_env.line[i - 1]))
	{
		i--;
		count++;
	}
	return (count);
}

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

int				auto_istabshift(char *str, int ret)
{
	if (ret == 3 && str[0] == 27 && str[1] == 91 && str[2] == 90)
		return (1);
	return (0);
}

int				auto_check_double(char *name)
{
	t_lstword	*tmp;

	tmp = g_data.lw;
	while (g_data.lw->next)
	{
		if (!(ft_strcmp(g_data.lw->name->name, name)))
		{
			g_data.lw = tmp;
			return (1);
		}
		g_data.lw = g_data.lw->next;
	}
	return (0);
}
