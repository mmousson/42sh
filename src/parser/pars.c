/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 19:16:45 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/06 15:48:31 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

static void			hist_add(char *str)
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

int					ft_pars(t_tok *token, char ***arge, char *str)
{
	t_tree			*tree;

	if (!token || !token->next
			|| (token->next->status == SPA && !token->next->next))
		return (0);
	if (str)
		hist_add(str);
	tree = ft_pars_line(token->next, 0, -2);
	ft_exec(tree, arge);
	return (0);
}
