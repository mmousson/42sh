/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 19:55:32 by oboutrol          #+#    #+#             */
/*   Updated: 2019/04/10 17:02:42 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"
#include <stdlib.h>
#include "libft.h"
#include <unistd.h>

t_tree		*ft_sep(t_tok *tok, int start, int end, char c)
{
	t_tok	*tmp;
	t_tree	*tree;
	int		pos;
	int		type;

	type = ft_get_ch(c);
	tmp = ft_go_start(tok, start);
	if (!(tree = ft_end_branch()))
		return (NULL);
	pos = start;
	tmp = ft_go_status(tmp, &pos, type, end);
	if (tmp && tmp->status == type)
	{
		if (!(tree->left = ft_select_pars(tok, start, pos - 1, c)))
			return (NULL);
		if (!(tree->right = ft_select_pars(tok, pos + 1, end, c)))
			return (NULL);
		tree->type = type;
		return (tree);
	}
	return (NULL);
}

t_tree		*ft_pars_line(t_tok *token, int start, int end)
{
	t_tok	*tok;
	t_tree	*tree;

	ft_cleans_spa(&start, &end, token);
	if (!(tree = ft_end_branch()))
		return (NULL);
	tok = ft_go_start(token, start);
	if (tok == NULL || (end != -2 && end < start))
		return (tree = ft_end_branch());
	else if ((tree = ft_sep(token, start, end, ';')))
		return (tree);
	else if ((tree = ft_pars_cmd(token, start, end)))
		return (tree);
	return (NULL);
}
