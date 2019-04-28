/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_del.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 12:00:43 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/28 14:47:44 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

static int			line_delword(char *str, int ret)
{
	int				i;

	i = g_env.cm->pos;
	if (line_isdelrword(str, ret))
	{
		while (g_env.line[i] && g_env.line[i] != ' ' && g_env.line[i] != '\n')
			i++;
		while (g_env.line[i] && (g_env.line[i] == ' ' || g_env.line[i] == '\n'))
			i++;
		g_env.line = line_delchar_bs(i - g_env.cm->pos);
	}
	else if (str[0] == CTRLW && ret == 1 && --i + 1)
	{
		while (i && (g_env.line[i] == ' ' || g_env.line[i] == '\n'))
			i--;
		while (i && g_env.line[i] != ' ' && g_env.line[i] != '\n')
			i--;
		g_env.line = line_delchar(g_env.cm->pos - i - 1);
		line_cursor_motion(MLEFT, g_env.cm->pos - i - 1);
	}
	else
		return (0);
	return (0);	
}

int					line_del(char *str, int ret)
{
	if (line_isdel(str, ret))
		g_env.line = line_delchar_bs(1);
	else if (str[0] == CTRLU && ret == 1)
	{
		g_env.line = line_delchar(g_env.cm->pos - g_env.p_size);
		line_home(1);
	}
	else if (str[0] == CTRLK && ret == 1)
		g_env.line = line_delchar_bs(g_env.len - g_env.cm->pos - 1);
	else if (str[0] == 127 && ret == 1)
	{
		g_env.line = line_delchar(1);
		g_env.del = 1;
		line_cursor_motion(MLEFT, 1);
		g_env.del = 0;
	}
	else
		return (line_delword(str, ret));
	return (1);
}
