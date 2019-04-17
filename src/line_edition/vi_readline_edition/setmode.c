/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setmode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 16:34:56 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/11 15:03:41 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

static int			ft_new_mode(t_env *env, t_emode mode)
{
	int				i;

	i = 0;
	while (i < MODE)
	{
		if (i == mode)
			env->mode->mode[i] = 1;
		else
			env->mode->mode[i] = 0;
		i++;
	}
	env->mode->n_select = 0;
	if (mode == MVI)
		env->mode->v_insert = 1;
	return (1);
}

int					ft_tmp(t_env *env, char *str)
{
	if (str[0] == -62 && str[1] == -70)
		return (ft_new_mode(env, MNORMAL));
	else if (str[0] == -30 && str[1] == -128 && str[2] == -109)
		return (ft_new_mode(env, MVI));
	else if (str[0] == -30 && str[1] == -119 && str[2] == -96)
		return (ft_new_mode(env, MREADLINE));
	return (0);
}

int					ft_reset_mode(t_env *env)
{
	if (!env->mode->mode[MVI])
		return (0);
	env->mode->v_insert = 1;
	env->mode->v_command = 0;
	env->mode->v_count = 0;
	return (0);
}
