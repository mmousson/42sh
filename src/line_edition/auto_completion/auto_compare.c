/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_compare.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 14:41:53 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/25 18:51:49 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

int				auto_comproot(void)
{
	char		*tmp_root;
	char		*tmp_var;

	tmp_root = auto_getroot();
	tmp_var = auto_getvar();
	if (ft_strcmp(tmp_root, g_data.root) || ft_strcmp(tmp_var, g_data.var))
	{
		auto_free();
		auto_filldata();
		ft_strdel(&tmp_root);
		ft_strdel(&tmp_var);
		return (auto_printword());
	}
	ft_strdel(&tmp_var);
	ft_strdel(&tmp_root);
	return (auto_choose());
}

int				auto_compath(void)
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
