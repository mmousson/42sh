/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_iskeymotion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 10:50:01 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/29 15:18:32 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

int					line_isleft(char *str, int ret)
{
	if (!ft_strcmp(g_env.tc->key[MLEFT], str)
			|| (g_env.mode->mode[MNORMAL] && str[0] == CTRLB && ret == 1)
			|| (g_env.mode->mode[MVI] && (str[0] == 'h' || str[0] == 127)
				&& ret == 1))
		return (1);
	return (0);
}

int					line_isright(char *str, int ret)
{
	if (!ft_strcmp(g_env.tc->key[MRIGHT], str)
			|| (g_env.mode->mode[MNORMAL] && str[0] == CTRLF && ret == 1)
			|| (g_env.mode->mode[MVI] && ft_strchr(" l", str[0]) && ret == 1))
		return (1);
	return (0);
}

int					line_ishome(char *str, int ret)
{
	if ((g_env.mode->mode[MNORMAL] && (str[0] == CTRLA && ret == 1))
			|| !ft_strcmp(g_env.tc->kh, str))
		return (1);
	return (0);
}

int					line_isend(char *str, int ret)
{
	if ((g_env.mode->mode[MNORMAL] && (str[0] == CTRLE && ret == 1))
			|| !ft_strcmp(TEND, str))
		return (1);
	return (0);
}

int					line_iscx(char *str, int ret)
{
	if (g_env.mode->mode[MNORMAL] && str[0] == CTRLX && ret == 1)
		return (1);
	return (0);
}
