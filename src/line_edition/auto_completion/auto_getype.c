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

static int			auto_checkchar(int i, char c, char prev)
{
	if (i - g_env.p_size + 1 == 0 || auto_newtoken(c, prev))
		return (0);
	if (auto_ispathcarac(g_env.line[i]))
		return (1);
	if (auto_isvar(c, prev))
		return (2);
	if (auto_isoption(c, prev))
		return (3);
	return (-1);
}

int				auto_getype(void)
{
	int			i;
	int			ret;

	i = g_env.cm->pos - 1;
	while ((ret = auto_checkchar(i, g_env.line[i], g_env.line[i - 1])) == -1)
		i--;
	if (ret)
		return (ret);
	while (i - g_env.p_size + 1 && g_env.line[i] == ' ')
		i--;
	if (i - g_env.p_size + 1 && (ft_isalpha(g_env.line[i])
			|| auto_ispathcarac(g_env.line[i])
			|| auto_isoption(g_env.line[i], g_env.line[i + 1])))
		return (1);
	return (0);
}
