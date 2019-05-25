/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 16:52:20 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/24 10:08:16 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

static int		auto_comproot(void)
{
	char		*tmp_root;

	tmp_root = auto_getroot();
	if (ft_strcmp(tmp_root, g_data.root))
	{
		auto_free();
		auto_filldata();
		ft_strdel(&tmp_root);
		return (auto_printword());
	}
	ft_strdel(&tmp_root);
	return (auto_choose());
}

static int		auto_compath(void)
{
	char		*tmp_root;
	char		*tmp_path;

	tmp_root = auto_getroot();
	tmp_path = auto_getpath();
	if (ft_strcmp(tmp_root, g_data.root)
			|| ft_strcmp(tmp_path, g_data.path[0]))
	{
		auto_free();
		auto_filldata();
		ft_strdel(&tmp_root);
		ft_strdel(&tmp_path);
		return (auto_printword());
	}
	ft_strdel(&tmp_root);
	ft_strdel(&tmp_path);
	return (auto_choose());
}

int				auto_option(void)
{
	if (g_data.status == 1)
	{
		if (g_data.type == 1)
			auto_compath();
		else if (g_data.type == 0 || g_data.type == 2)
			auto_comproot();
	}
	else if (g_data.status == 2)
		return (auto_choose());
	else
		return (0);
	return (1);
}

int				auto_completion(char *str, int ret)
{
	int			tmp;

	if (str[0] == '\t' && ret == 1)
	{
		tmp = auto_getype();
		if (g_data.status != 2 && tmp != g_data.type)
			auto_free();
		if (auto_isblank())
			line_paste("    ", g_env.count);
		else if (auto_option())
			return (1);
		else
		{
			auto_filldata();
			return (auto_printword());
		}
	}
	else
		return (0);
	return (1);
}
