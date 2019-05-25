/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_printvar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 16:59:16 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/25 11:28:30 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"
#include "sh42.h"

static char			*auto_getnamevar(char *str)
{
	int				i;
	char			*name;

	i = 0;
	name = NULL;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		name = ft_strsub(str, 0, i);
	return (name);
}

static void			auto_printvarenv(void)
{
	int				i;
	char			*name;

	i = 0;
	if (!g_env.env || !g_env.env[0])
		return ;
	while ((*g_env.env)[i])
	{
		if ((name = auto_getnamevar((*g_env.env)[i])))
		{
			if (auto_checkroot(name, g_data.root))
				auto_lstword(name, &name, 0);
			ft_strdel(&name);
		}
		i++;
	}
}

void				auto_printvar(void)
{
	t_vars			*tmp;

	tmp = g_shell_var_list;
	if (g_data.type != 2)
		return ;
	auto_printvarenv();
	while (g_shell_var_list)
	{
		if (auto_checkroot(g_shell_var_list->name, g_data.root))
			auto_lstword(g_shell_var_list->name, &g_shell_var_list->name, 0);
		g_shell_var_list = g_shell_var_list->next;
	}
	g_shell_var_list = tmp;
}
