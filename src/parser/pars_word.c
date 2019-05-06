/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 18:26:02 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/04 16:15:20 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"
#include <stdlib.h>

void		til_word(t_tok *token, int start, int end, t_tree **tree)
{
	if ((*tree)->type == TIL)
	{
		(*tree)->left = NULL;
		(*tree)->right = ft_pars_nword(token, start, end);
	}
	else
	{
		ft_free_tree(*tree);
		*tree = ft_pars_nword(token, start, end);
	}
}

t_tree		*ft_word_sp(t_tok *token, int start, int end)
{
	t_tok	*tok;
	t_tree	*tree;

	if (!(tree = ft_end_branch()))
		return (NULL);
	tok = ft_go_start(token, start);
	if (tok && tok->status == TIL)
	{
		tok = tok->next;
		tree->type = TIL;
		start++;
	}
	if (tok && (end == -2 || start <= end))
		til_word(token, start, end, &tree);
	if (tree && tree->type != ZER)
		return (tree);
	return (ft_free_tree(tree));
}

t_tree		*ft_pars_word(t_tok *token, int start, int end)
{
	t_tree	*tree;

	if ((tree = ft_word_sp(token, start, end)))
		return (tree);
	return (NULL);
}
