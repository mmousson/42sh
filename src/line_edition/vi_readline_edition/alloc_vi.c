/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_vi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:59:39 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/11 15:16:31 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "line_edition.h"
#include "libft.h"

int				ft_hash_insert(t_env *env)
{
	char		*fresh;

	if (env->len >= BUFF_SIZE)
		return (0);
	if (!(fresh = ft_strnew(env->len + 1)))
		ft_errorterm(TMALLOC, env);
	ft_strncpy(fresh, env->line, env->p_size);
	fresh[env->p_size] = '#';
	ft_strcpy(&(fresh[env->p_size + 1]), &(env->line[env->p_size]));
	ft_strdel(&(env->line));
	env->line = fresh;
	ft_reset_history(env);
	ft_strdel(&env->oldline);
	if (!(env->oldline = ft_strdup(env->line)))
		ft_errorterm(TMALLOC, env);
	return (0);
}
