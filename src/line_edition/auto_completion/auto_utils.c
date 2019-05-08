/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 11:54:13 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/06 12:31:51 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

int				auto_isblank(void)
{
	int			i;

	i = g_env.p_size;
	while (g_env.line[i] && (g_env.line[i] == ' ' || g_env.line[i] == '\t'))
		i++;
	if (!g_env.line[i])
		return (1);
	return (0);
}
