/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 18:26:02 by oboutrol          #+#    #+#             */
/*   Updated: 2019/04/13 07:34:05 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"
#include <stdlib.h>
#include "libft.h"
#include <unistd.h>

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
		if (tok->content)
			tree->content = ft_strdup(tok->content);
		tree->type = TIL;
		start++;
	}
	if (tok && (end == -2 || start <= end))
	{
		if (tree->type == TIL)
		{
			tree->left = NULL;
			if ((tree->right = ft_pars_nword(token, start, end)))
				return (tree);
		}
		else
		{
			if ((tree = ft_pars_nword(token, start, end)))
				return (tree);
		}
	}
	return (NULL);
}

t_tree		*ft_pars_word(t_tok *token, int start, int end)
{
	t_tree	*tree;

	if ((tree = ft_word_sp(token, start, end)))
		return (tree);
	return (NULL);
}
