/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 15:44:45 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/01 14:49:26 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

int				vi_history(char *str, int ret)
{
	if (g_env.mode->v_del)
		return (0);
	if (str[0] == 'j' && ret == 1)
		line_get_dhistory(g_env.count);
	else if (str[0] == 'k' && ret == 1)
		line_get_uhistory(g_env.count);
	else
		return (0);
	g_env.mode->v_visual = 0;
	g_env.mode->v_yank = 0;
	vi_reset_count(str);
	return (1);
}
