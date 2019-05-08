/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_undo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 14:27:09 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/02 15:04:53 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

int					line_undo(char *str, int ret)
{
	t_undo			*tmp;
	char			*oldline;

	if (!g_env.mode->undo)
		return (0);
	if (str[0] == CTRLUND && ret == 1)
	{
		tmp = g_env.mode->undo;
		oldline = g_env.line;
		while (g_env.mode->undo->next)
			g_env.mode->undo = g_env.mode->undo->next;
		if (!(g_env.line = ft_strdup(g_env.mode->undo->command)))
			sh_errorterm(TMALLOC);
		vi_reset_cursor(tmp, 1);
		g_env.mode->undo = tmp;
		vi_delundo();
		ft_strdel(&oldline);
		return (1);
	}
	return (0);
}
