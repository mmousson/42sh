/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 19:16:45 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/31 23:21:38 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"
#include "history.h"

int					pars_tok(t_tok *token, char ***arge, char *str)
{
	t_tree			*tree;
	t_tok			*tmp;
	int				sep;

	if (!token || !token->next
			|| (token->next->status == SPA && !token->next->next))
		return (0);
	tmp = token->next;
	if (str)
		hist_update(str);
	while (tmp)
	{
		if (expand_token(tmp, arge))
			return (0);
		tree = ft_pars_line(tmp, 0, -2);
		while (tmp && !pars_is_delimiter(tmp->status))
			tmp = tmp->next;
		if (tmp)
		{
			sep = tmp->status;
			tmp = tmp->next;
		}
		else
			sep = SMC;
		ft_print_tree(tree);
		ft_exec(tree, arge, sep);
	}
	return (0);
}
