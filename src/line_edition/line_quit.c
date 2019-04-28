/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_quit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 09:29:41 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/28 11:44:57 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

int				line_ctrld(void)
{
	g_env.ctrld = 1;
	return (0);
}

int				line_return(void)
{
	if (g_env.mode->mode[MVI])
	{
		ft_bzero(g_env.mode->s_buffer, sizeof(g_env.mode->s_buffer));
		vi_free_undo(g_env.mode->undo);
		g_env.mode->undo = NULL;
		line_end();
		return (vi_reset_mode(1, 0, 0));
	}
	return (line_end());
}
