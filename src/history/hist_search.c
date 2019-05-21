/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 09:45:50 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/21 18:20:03 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

int				hist_search(char *str, int ret)
{
	(void)str;
	(void)ret;
	if (!g_env.search)
	{
		g_env.search = 1;
		hist_alloc_search(HIST);
		return (1);
	}
	return (0);
}

int				hist_lst(char *str, int ret)
{
	if (str[0] == 27 && ret == 1)
		return (line_escap());
	if (str[0] <= 126 && str[0] >= 32)
	{
		g_env.line = hist_addstr(str);
		line_cursor_motion(MRIGHT, ret);
	}
	else if (str[0] == 127 && ret == 1)
	{
		g_env.line = hist_delchar();
		line_cursor_motion(MLEFT, 1);
	}
	return (1);
}

