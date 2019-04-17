/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getvi_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 16:16:24 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/11 19:37:23 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"
#include "libft.h"

int					ft_vi(t_env *env, char *str)
{
	int				i;

	i = -1;
	if (!ft_tmp(env, str))
		return (0);
	return (1);
}

static int			ft_vi_insert(t_env *env, char *str, int ret)
{
	if (str[0] == 27 && ret == 1)
	{
		env->mode->v_command = 1;
		env->mode->v_insert = 0;
		return (1);
	}
	if (ft_line_ascii(env, str, ret))
		return (1);
	else if (ft_line_arrow(env, str))
		return (1);
	else if (ft_line_history(env, str))
		return (1);
	return (0);
}

int					ft_line_vi(t_env *env, char *str, int ret)
{
	int				reset;

	reset = 1;
	if (ft_tmp(env, str) && !env->mode->mode[MVI])
		return (0);
	if (str[0] == '\n' && ret == 1)
		return (ft_reset_mode(env));
	if (env->mode->v_insert)
		return (ft_vi_insert(env, str, ret));
	else if (env->mode->v_command)
		reset = ft_vi_command(env, str, ret);
	if (!reset)
		return (ft_reset_mode(env));
	return (1);
}
