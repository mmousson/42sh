/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump_words.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 03:54:03 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/25 09:04:51 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

void				ft_home(int blank)
{
	int				i;

	ft_cursor_motion(MLEFT, g_env.cm->pos - g_env.p_size);
	i = g_env.cm->pos;
	if (!blank)
	{
		while (g_env.line[i] && g_env.line[i] == ' ')
			i++;
		ft_cursor_motion(MRIGHT, i - g_env.cm->pos);
	}
}

void				ft_end(void)
{
	ft_cursor_motion(MRIGHT, g_env.len - g_env.cm->pos);
}

void				ft_ljump(void)
{
	int				i;

	i = g_env.cm->pos - 1;
	while (i && (g_env.line[i] == ' ' || g_env.line[i] == '\n'))
		i--;
	while (i && g_env.line[i] != ' ' && g_env.line[i] != '\n')
		i--;
	if (g_env.line[i + 1])
		ft_cursor_motion(MLEFT, g_env.cm->pos - i - 1);
}

void				ft_rjump(void)
{
	int				i;

	i = g_env.cm->pos;
	while (g_env.line[i] && g_env.line[i] != ' ' && g_env.line[i] != '\n')
		i++;
	while (g_env.line[i] && (g_env.line[i] == ' ' || g_env.line[i] == '\n'))
		i++;
	ft_cursor_motion(MRIGHT, i - g_env.cm->pos);
}
