/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_getype.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 12:12:03 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/25 15:06:39 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

int				auto_ispathcarac(char c)
{
	if (c == '/' || c == '<' || c == '>')
		return (1);
	return (0);
}

int				auto_newtoken(char c, char prev)
{
	if ((c == ' ' && prev != '\\') || c == '|' || c == '&' || c == '(')
		return (1);
	return (0);
}

int				auto_isvar(char c, char prev)
{
	if (c == '$' || (c == '{' && prev == '$'))
		return (1);
	return (0);
}

int				auto_getype(void)
{
	int			i;

	i = g_env.cm->pos - 1;
	while (i - g_env.p_size + 1
			&& !auto_newtoken(g_env.line[i], g_env.line[i - 1])
			&& !auto_isvar(g_env.line[i], g_env.line[i - 1]))
	{
		if (auto_ispathcarac(g_env.line[i]))
			return (1);
		if (auto_isvar(g_env.line[i], g_env.line[i - 1]))
			return (2);
		i--;
	}
	if (i - g_env.p_size + 1 && auto_isvar(g_env.line[i], g_env.line[i - 1]))
		return (2);
	if (i - g_env.p_size + 1 && g_env.line[i] != ' ')
		return (0);
	while (i - g_env.p_size + 1 && g_env.line[i] == ' ')
		i--;
	if (i - g_env.p_size + 1 && (ft_isalpha(g_env.line[i])
				|| (auto_ispathcarac(g_env.line[i]))))
		return (1);
	return (0);
}
