/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 15:44:45 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/25 10:36:16 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

int				ft_vi_history(char *str, int ret)
{
	if (g_env.mode->v_del)
		return (0);
	if (str[0] == 'j' && ret == 1)
		ft_get_dhistory(g_env.mode->v_count);
	else if (str[0] == 'k' && ret == 1)
		ft_get_uhistory(g_env.mode->v_count);
	else
		return (0);
	g_env.mode->v_visual = 0;
	g_env.mode->v_yank = 0;
	ft_reset_count(str);
	return (1);
}
