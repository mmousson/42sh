/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 12:59:22 by oboutrol          #+#    #+#             */
/*   Updated: 2019/07/03 17:02:50 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

int					get_sep(t_tok *tmp)
{
	int				sep;

	if (tmp)
	{
		sep = tmp->status;
		tmp = tmp->next;
	}
	else
		sep = SMC;
	return (sep);
}

int					pars_tok(t_tok *token, char ***arge)
{
	t_tree			*tree;
	t_tok			*tmp;
	int				sep;

	if (!token || !token->next
			|| (token->next->status == SPA && !token->next->next))
		return (0);
	tmp = token->next;
	while (tmp)
	{
		if (expand_token(tmp, arge, 0, 0))
			return (0);
		tree = ft_pars_line(tmp, 0, -2);
		while (tmp && !pars_is_delimiter(tmp->status))
			tmp = tmp->next;
		sep = get_sep(tmp);
		ft_exec(tree, arge, sep);
		if (tmp)
			tmp = tmp->next;
	}
	return (0);
}
