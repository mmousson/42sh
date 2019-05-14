/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_quit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 09:29:41 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/13 21:06:57 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

int				line_ctrld(void)
{
/*	if (!g_env.jobs && active_jobs_list && g_env.ctrld)
		ft_putstr("There are stopped jobs.\n");
	if (active_jobs_list && g_env.ctrld)
		g_env.jobs++;*/
	g_env.ctrld = 1;
	g_env.count = 0;
	return (0);
}

int				line_return(void)
{
	if (g_data.status == 2)
		return (auto_return());
	g_env.jobs = 0;
	if (g_env.mode->mode[MVI])
	{
		ft_bzero(g_env.s_buffer, sizeof(g_env.s_buffer));
		vi_free_undo(g_env.mode->undo);
		g_env.mode->undo = NULL;
		line_end();
		return (vi_reset_mode(1, 0, 0));
	}
	g_env.count = 0;
	if (g_env.mode->n_select)
		line_escap_cpy(1);
	return (line_end());
}

int				line_escap(void)
{
	if (g_env.mode->mode[MVI])
		vi_reset_mode(0, 1, 0);
	else if (g_env.mode->n_select)
		line_escap_cpy(1);
	if (g_env.mode->mode[MNORMAL])
	{
		g_env.mode->v_command = 1;
		g_env.count = 0;
	}
	return (1);
}
