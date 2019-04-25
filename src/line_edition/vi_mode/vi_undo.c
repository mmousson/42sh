/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_undo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 17:58:52 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/25 10:40:41 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

int					ft_vi_undo(char *str, int ret)
{
	t_undo			*tmp;

	if (!g_env.mode->undo)
		return (1);
	if (str[0] == 'u' && ret == 1)
	{
		/*if (!ft_delundo(g_env.mode->undo))
			return (1);*/
		tmp = g_env.mode->undo;
		ft_strdel(&(g_env.line));
		while (g_env.mode->undo->next)
			g_env.mode->undo = g_env.mode->undo->next;
		if (!(g_env.line = ft_strdup(g_env.mode->undo->command)))
			ft_errorterm(TMALLOC);
		g_env.mode->undo = tmp;
		ft_delundo(g_env.mode->undo);
	}
	else
		return (0);
	return (1);
}
