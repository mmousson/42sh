/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_repeat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 11:18:36 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/27 17:55:55 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

void		vi_repeat(void)
{
	if (g_env.mode->v_lastc == 'f')
		g_env.mode->v_prior[0] = 1;
	else if (g_env.mode->v_lastc == 'F')
		g_env.mode->v_prior[1] = 1;
	else if (g_env.mode->v_lastc == 't')
		g_env.mode->v_prior[2] = 1;
	else if (g_env.mode->v_lastc == 'T')
		g_env.mode->v_prior[3] = 1;
	vi_get_prior_flag(&(g_env.mode->v_lasta), 1);
}

void		vi_rev_repeat(void)
{
	if (g_env.mode->v_lastc == 'f')
		g_env.mode->v_prior[1] = 1;
	else if (g_env.mode->v_lastc == 'F')
		g_env.mode->v_prior[0] = 1;
	else if (g_env.mode->v_lastc == 't')
		g_env.mode->v_prior[3] = 1;
	else if (g_env.mode->v_lastc == 'T')
		g_env.mode->v_prior[2] = 1;
	vi_get_prior_flag(&(g_env.mode->v_lasta), 1);
}
