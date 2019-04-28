/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_iskeydel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 11:53:36 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/28 12:49:00 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

int					line_isdel(char *str, int ret)
{
	if (g_env.mode->mode[MNORMAL]
			&& (!ft_strcmp(g_env.tc->kd, str)
				|| (str[0] == CTRLD && ret == 1)))
		return (1);
	return (0);
}

int					line_isdelrword(char *str, int ret)
{
	if (ret == 3 && str[0] == -30 && str[1] == -120 && str[2] == -126)
		return (1);
	return (0);
}
