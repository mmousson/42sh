/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 19:16:45 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/14 17:58:36 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"
#include "history.h"

int					pars_tok(t_tok *token, char ***arge, char *str)
{
	t_tree			*tree;

	if (!token || !token->next
			|| (token->next->status == SPA && !token->next->next))
		return (0);
	if (str)
		hist_update(str);
	tree = ft_pars_line(token->next, 0, -2);
	ft_exec(tree, arge);
	return (0);
}
