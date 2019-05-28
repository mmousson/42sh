/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_jump_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 13:16:46 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/28 16:02:40 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

static void		vi_endrbjump(void)
{
	int			i;

	i = g_env.cm->pos + 1;
	if (i >= g_env.len)
		return ;
	while (g_env.line[i] && (g_env.line[i] == ' ' || g_env.line[i] == '\n'))
		i++;
	while (g_env.line[i] && g_env.line[i] != ' ' && g_env.line[i] != '\n')
		i++;
	if (g_env.line[i - 1])
		line_cursor_motion(MRIGHT, i - g_env.cm->pos - 1);
}

static void		vi_endrjump(void)
{
	int			i;

	i = g_env.cm->pos + 1;
	if (i >= g_env.len)
		return ;
	while (g_env.line[i] && ft_strchr(" \n", g_env.line[i]))
		i++;
	if (g_env.line[i] && !line_isword(g_env.line[i]))
		while (g_env.line[i] && !line_isword(g_env.line[i]))
			i++;
	else
		while (g_env.line[i] && line_isword(g_env.line[i]))
			i++;
	if (g_env.line[i - 1])
		line_cursor_motion(MRIGHT, i - g_env.cm->pos - 1);
}

void			vi_ejump(int count, char c)
{
	while (--count + 1)
	{
		if (c == 'e')
			vi_endrjump();
		else
			vi_endrbjump();
	}
}

void			vi_pipejump(int count)
{
	line_home(1);
	line_cursor_motion(MRIGHT, count - 1);
}
