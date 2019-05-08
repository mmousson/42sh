/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 16:52:20 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/07 10:36:07 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

static void		auto_proposition(int type)
{
	char		*path;
	char		*root;

	root = auto_getroot();
	if (type == 1)
	{
		path = auto_getpath();
		auto_printword(path, root);
	}
	else if (!type)
		return ; //command/variable/built_in/alias;
}

int				auto_completion(char *str, int ret)
{
	int			type;

	if (str[0] == '\t' && ret == 1)
	{
		if (auto_isblank())
			line_paste("    ", g_env.count);
		else
		{
			type = auto_getype();
			auto_proposition(type);
		}
	}
	else
		return (0);
	return (1);
}
