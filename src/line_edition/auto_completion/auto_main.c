/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 16:52:20 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/25 18:30:35 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

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
