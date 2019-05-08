/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_jumpoccur.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 10:59:13 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/28 09:35:32 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

static void			vi_fjump(char c, int len)
{
	int				i;

	i = g_env.cm->pos + 1;
	if (i > len)
		return ;
	while (g_env.line[i] && g_env.line[i] != c)
		i++;
	line_cursor_motion(MRIGHT, i - g_env.cm->pos);
}

static void			vi_bigfjump(char c)
{
	int				i;

	i = g_env.cm->pos - 1;
	while (i && g_env.line[i] != c)
		i--;
	if (i || g_env.line[0] == c)
		line_cursor_motion(MLEFT, g_env.cm->pos - i);
}

static void			vi_tjump(char c, int len)
{
	line_cursor_motion(MRIGHT, 1);
	vi_fjump(c, len);
	line_cursor_motion(MLEFT, 1);
}

static void			vi_bigtjump(char c)
{
	line_cursor_motion(MLEFT, 1);
	vi_bigfjump(c);
	line_cursor_motion(MRIGHT, 1);
}

void				vi_jump_occur(char c, int i, int count)
{
	int				len;

	len = (int)ft_strlen(g_env.line);
	while (--count + 1)
	{
		if (!i)
			vi_fjump(c, len);
		else if (i == 1)
			vi_bigfjump(c);
		else if (i == 2)
			vi_tjump(c, len);
		else if (i == 3)
			vi_bigtjump(c);
	}
}
