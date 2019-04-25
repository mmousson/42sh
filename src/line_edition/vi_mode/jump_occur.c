/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump_occur.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 10:59:13 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/25 09:52:47 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

static void			ft_fjump(char c)
{
	int				i;

	i = g_env.cm->pos + 1;
	if (i > g_env.len)
		return ;
	while (g_env.line[i] && g_env.line[i] != c)
		i++;
	ft_cursor_motion(MRIGHT, i - g_env.cm->pos);	
}

static void			ft_bigfjump(char c)
{
	int				i;

	i = g_env.cm->pos - 1;
	while (i && g_env.line[i] != c)
		i--;
	if (i || g_env.line[0] == c)
		ft_cursor_motion(MLEFT, g_env.cm->pos - i);
}

static void			ft_tjump(char c)
{
	ft_cursor_motion(MRIGHT, 1);
	ft_fjump(c);
	ft_cursor_motion(MLEFT, 1);
}

static void			ft_bigtjump(char c)
{
	ft_cursor_motion(MLEFT, 1);
	ft_bigfjump(c);
	ft_cursor_motion(MRIGHT, 1);
}
void				ft_jump_occur(char c, int i, int count)
{
	while (--count + 1)
	{
		if (!i)
			ft_fjump(c);
		else if (i == 1)
			ft_bigfjump(c);
		else if (i == 2)
			ft_tjump(c);
		else if (i == 3)
			ft_bigtjump(c);
	}
}
