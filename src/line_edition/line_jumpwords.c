/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_jumpwords.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 03:54:03 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/03 12:11:55 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

void				line_home(int blank)
{
	int				i;

	line_cursor_motion(MLEFT, g_env.cm->pos - g_env.p_size);
	i = g_env.cm->pos;
	if (!blank)
	{
		while (g_env.line[i] && g_env.line[i] == ' ')
			i++;
		line_cursor_motion(MRIGHT, i - g_env.cm->pos);
	}
}

int					line_end(void)
{
	line_cursor_motion(MRIGHT, g_env.len - g_env.cm->pos);
	return (0);
}

void				line_ljump(void)
{
	int				i;
	int				count;

	count = g_env.count + 1;
	while (--count)
	{
		i = g_env.cm->pos - 1;
		while (i && (g_env.line[i] == ' ' || g_env.line[i] == '\n'))
			i--;
		while (i && g_env.line[i] != ' ' && g_env.line[i] != '\n')
			i--;
		if (g_env.line[i + 1])
			line_cursor_motion(MLEFT, g_env.cm->pos - i - 1);
	}
}

void				line_rjump(void)
{
	int				i;
	int				count;

	count = g_env.count + 1;
	while (--count)
	{
		i = g_env.cm->pos;
		while (g_env.line[i] && g_env.line[i] != ' ' && g_env.line[i] != '\n')
			i++;
		while (g_env.line[i] && (g_env.line[i] == ' ' || g_env.line[i] == '\n'))
			i++;
		line_cursor_motion(MRIGHT, i - g_env.cm->pos);
	}
}
