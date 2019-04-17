/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getrd_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 16:20:32 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/10 19:31:51 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

int					ft_read_line(t_env *env, char *str)
{
	(void)env;
	(void)str;
	return (0);
}

int					ft_line_readline(t_env *env, char *str, int ret)
{
	if (ft_tmp(env, str) && !env->mode->mode[MREADLINE])
		return (0);
	(void)ret;
	return (0);
}
