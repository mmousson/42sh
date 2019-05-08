/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_delenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 04:08:34 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/04 16:15:34 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"
#include <stdlib.h>

static void			line_free_history(t_history *ry)
{
	if (ry->next)
		line_free_history(ry->next);
	if (ry->line)
		ft_strdel(&(ry->line));
	ft_memdel((void**)&(ry));
}

void				vi_free_undo(t_undo *undo)
{
	if (!undo)
		return ;
	if (undo)
		vi_free_undo(undo->next);
	if (undo->command)
		ft_strdel(&(undo->command));
	ft_memdel((void**)&(undo));
}

void				line_delenv(void)
{
	if (g_env.tc)
		ft_memdel((void**)&(g_env.tc));
	if (g_env.cm)
		ft_memdel((void**)&(g_env.cm));
	if (g_env.oldline)
		ft_strdel(&(g_env.oldline));
	if (g_env.ry)
		line_free_history(g_env.ry);
	if (g_env.mode)
	{
		vi_free_undo(g_env.mode->undo);
		ft_memdel((void**)&(g_env.mode));
	}
	if (g_env.cx)
		ft_memdel((void**)&(g_env.cx));
}
