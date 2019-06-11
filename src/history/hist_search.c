/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 09:45:50 by roliveir          #+#    #+#             */
/*   Updated: 2019/06/11 17:23:33 by roliveir         ###   ########.fr       */
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

static int		hist_checksearch(t_history **tmp)
{
	if (!g_env.ry->next)
	{
		g_env.ry = *tmp;
		return (0);
	}
	return (1);
}

static int		hist_initsearch(char c)
{
	int			index;
	t_history	*tmp;

	tmp = g_env.ry;
	index = c == CTRLR ? g_env.h_index + 1 : 1;
	while (g_env.ry->next && --index)
		g_env.ry = g_env.ry->next;
	if (!g_env.ry->next && index)
	{
		g_env.ry = tmp;
		return (-1);
	}
	index = c == CTRLR ? g_env.h_index : 0;
	return (index);
}

static void		hist_searchline(char c)
{
	t_history	*tmp;
	int			forwards;
	int			index;
	char		buff[BUFF_SIZE + 1];

	ft_strcpy(buff, g_env.line);
	tmp = g_env.ry;
	forwards = 0;
	if ((index = hist_initsearch(c)) == -1)
		return ;
	while (g_env.ry->next && ++index)
	{
		if ((forwards = hist_strstr(g_env.ry->line, g_env.h_word)) > -1)
		{
			g_env.h_index = index;
			hist_addline(g_env.ry->line, forwards);
			break ;
		}
		g_env.ry = g_env.ry->next;
	}
	if (!hist_checksearch(&tmp))
		return ;
	g_env.ry = tmp;
	if (!ft_strcmp(buff, g_env.line))
		hist_searchline(CTRLR);
}

int				hist_lst(char *str, int ret)
{
	if (str[0] == 27 && ret == 1)
		return (line_escap());
	if (str[0] <= 126 && str[0] >= 32)
		hist_addstr(str);
	else if (str[0] == 127 && ret == 1)
		hist_delchar();
	else if (ret != 1 || str[0] != CTRLR)
		return (1);
	if (g_env.h_word)
		hist_searchline(str[0]);
	return (1);
}
