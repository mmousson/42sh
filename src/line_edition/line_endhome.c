/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_endhome.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 17:19:05 by roliveir          #+#    #+#             */
/*   Updated: 2019/06/11 17:20:04 by roliveir         ###   ########.fr       */
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
