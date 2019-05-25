/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_expend.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 17:16:07 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/23 13:37:44 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

static char		*hist_getlast(void)
{
	t_history	*tmp;
	char		*result;

	result = NULL;
	tmp = g_env.ry;
	if (!g_env.ry)
		return (NULL);
	while (g_env.ry->next)
		g_env.ry = g_env.ry->next;
	if (g_env.ry->line)
		result = ft_strdup(g_env.ry->line);
	g_env.ry = tmp;
	return (result);
}

static char		*hist_getnbr(int index)
{
	t_history	*tmp;
	char		*result;

	result = NULL;
	tmp = g_env.ry;
	if (!g_env.ry)
		return (NULL);
	while (g_env.ry->next)
		g_env.ry = g_env.ry->next;
	while (--index && g_env.ry->prev)
		g_env.ry = g_env.ry->prev;
	if (!index && g_env.ry->line)
		result = ft_strdup(g_env.ry->line);
	g_env.ry = tmp;
	return (result);
}

static char		*hist_getnbrneg(int index)
{
	t_history	*tmp;
	char		*result;

	result = NULL;
	index = -index;
	tmp = g_env.ry;
	if (!g_env.ry)
		return (NULL);
	while (--index && g_env.ry->next)
		g_env.ry = g_env.ry->next;
	if (!index && g_env.ry->line)
		result = ft_strdup(g_env.ry->line);
	g_env.ry = tmp;
	return (result);
}

char			*hist_getexpend(char **str)
{
	int			len;
	char		*result;

	if (!str || !*str)
		return (NULL);
	result = NULL;
	len = ft_strlen(*str);
	if ((*str)[0] == '!' && len == 1)
		result = hist_getlast();
	else if (ft_isdigit((*str)[0]))
		result = hist_getnbr(ft_atoi(*str));
	else if ((*str)[0] == '-')
		result = hist_getnbrneg(ft_atoi(*str));
	ft_strdel(str);
	return (result);
}
