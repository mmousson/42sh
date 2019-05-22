/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 09:45:50 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/22 13:48:10 by roliveir         ###   ########.fr       */
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

void			hist_searchline(void)
{
	t_history	*tmp;
	int			forwards;

	tmp = g_env.ry;
	forwards = 0;
	while (g_env.ry->next)
	{
		if ((forwards = hist_strstr(g_env.ry->line, g_env.h_word)) > -1)
		{
			hist_addline(g_env.ry->line, forwards);
			break ;
		}
		g_env.ry = g_env.ry->next;
	}
	g_env.ry = tmp;
}

int				hist_lst(char *str, int ret)
{
	if (str[0] == 27 && ret == 1)
		return (line_escap());
	if (str[0] <= 126 && str[0] >= 32)
		hist_addstr(str);
	else if (str[0] == 127 && ret == 1)
		hist_delchar();
	hist_searchline();
	return (1);
}
