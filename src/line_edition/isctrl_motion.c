/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isctrl_motion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 10:50:01 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/26 13:06:39 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

int					ft_rd_left(char *str, int ret)
{
	if (!ft_strcmp(g_env.tc->key[MLEFT], str)
			|| (g_env.mode->mode[MNORMAL] && str[0] == CTRLB && ret == 1))
		return (1);
	return (0);
}

int					ft_rd_right(char *str, int ret)
{
	if (!ft_strcmp(g_env.tc->key[MRIGHT], str)
			|| (g_env.mode->mode[MNORMAL] && str[0] == CTRLF && ret == 1))
		return (1);
	return (0);
}
