/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_expend.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 17:16:07 by roliveir          #+#    #+#             */
/*   Updated: 2019/06/09 11:26:53 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

static char		*hist_getlast(void)
{
	char		*result;

	if (!g_env.ry || !g_env.ry->line)
		return (NULL);
	result = ft_strdup(g_env.ry->line);
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

static char		*hist_getstr(char *str)
{
	char		*result;
	t_history	*tmp;
	size_t		len;

	result = NULL;
	tmp = g_env.ry;
	len = ft_strlen(str);
	while (g_env.ry)
	{
		if (!ft_strncmp(g_env.ry->line, str, len))
		{
			result = ft_strdup(g_env.ry->line);
			break ;
		}
		g_env.ry = g_env.ry->next;
	}
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
	else
		result = hist_getstr(*str);
	return (result);
}
