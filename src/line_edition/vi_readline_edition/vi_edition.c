/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_edition.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 17:17:19 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/11 19:37:25 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"
#include "libft.h"

void				ft_get_count(t_env *env, char *str)
{
	int			tmp;

	tmp = ft_atoi(str);
	if (tmp || str[0] == '0')
		env->mode->v_count = env->mode->v_count * 10 + tmp;
	else if (!env->mode->v_count)
		env->mode->v_count = 1;
}

void				ft_reset_count(t_env *env, char *str)
{
	int			tmp;

	tmp = ft_atoi(str);
	if (!tmp && str[0] && env->mode->v_count)
		env->mode->v_count = 0;
}
