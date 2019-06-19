/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_inverse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 13:26:26 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/05 16:44:09 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

static void			line_swap(char *a, char *b)
{
	char			tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void			line_invleft(void)
{
	int				i;

	i = g_env.cm->pos;
	if (i < g_env.p_size + 2 && g_env.len - g_env.p_size < 3)
		return ;
	if (i == g_env.p_size)
	{
		line_swap(&g_env.line[i], &g_env.line[i + 1]);
		line_cursor_motion(MRIGHT, 2);
	}
	else if (i == g_env.len - 1)
		line_swap(&g_env.line[i - 1], &g_env.line[i - 2]);
	else
	{
		line_swap(&g_env.line[i], &g_env.line[i - 1]);
		line_cursor_motion(MRIGHT, 1);
	}
}

static void			line_invright(void)
{
	int				i;

	i = g_env.cm->pos;
	if (g_env.cm->pos > g_env.len - 3)
		return ;
	line_swap(&g_env.line[i], &g_env.line[i + 1]);
	line_cursor_motion(MRIGHT, 1);
}

int					line_inverse(char *str, int ret)
{
	if ((str[0] == CTRLT || str[0] == CTRLT) && ret == 1)
		vi_add_undo();
	if (str[0] == CTRLT && ret == 1)
		line_invleft();
	else if (line_isaltt(str, ret))
		line_invright();
	else
		return (0);
	vi_reset_count(str);
	vi_add_undo();
	return (1);
}
