/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 19:16:45 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/13 20:33:51 by roliveir         ###   ########.fr       */
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
		hist_add(str);
	ft_print_token(token);
	tree = ft_pars_line(token->next, 0, -2);
	(void)arge;
	//ft_exec(tree, arge);
	return (0);
}
