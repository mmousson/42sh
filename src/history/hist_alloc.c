/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 10:09:40 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/13 19:57:06 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

void				hist_add(char *str)
{
	t_history		*tmp;
	t_history		*new;

	tmp = g_env.ry;
	if (!(new = (t_history*)ft_memalloc(sizeof(t_history))))
		sh_errorterm(TMALLOC);
	new->next = tmp;
	new->prev = NULL;
	if (tmp)
		tmp->prev = new;
	if (!(new->line = ft_strdup(str)))
		sh_errorterm(TMALLOC);
	g_env.ry = new;
}
