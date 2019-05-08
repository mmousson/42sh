/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_red.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 14:59:06 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/04 16:13:46 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"
#include <stdlib.h>
#include "libft.h"

t_tree		*ft_dash(t_tok *token, int start, int end)
{
	t_tok	*tok;
	t_tree	*tree;

	tok = ft_go_start(token, start);
	if (tok && tok->status == DAS)
	{
		if (!(tree = ft_end_branch()))
			return (NULL);
		tree->right = ft_pars_pipe(token, start + 1, end);
		tree->left = NULL;
		tree->type = DAS;
		if (tok->content)
			tree->content = ft_strdup(tok->content);
		return (tree);
	}
	return (ft_pars_pipe(token, start, end));
}

t_tree		*ft_red_right(t_tok *token, int start, int end, int typ)
{
	t_tok	*tok;
	t_tree	*tree;
	int		pos;
	int		pos2;

	tok = ft_go_start(token, start);
	pos = start;
	tok = ft_go_status(tok, &pos, typ, end);
	if (tok && tok->status == typ)
	{
		if (!(tree = ft_end_branch()))
			return (NULL);
		pos2 = pos + 1;
		if (!(tree->right = ft_dash(token, pos2, end)))
			if (pos2 <= end || (end == -2 && tok->next != NULL))
				return (ft_free_tree(tree));
		pos2 = pos - 1;
		if (!(tree->left = ft_pars_word(token, start, pos2)))
			if (start <= pos2)
				return (ft_free_tree(tree));
		tree->type = typ;
		tree->content = ft_strdup(tok->content);
		return (tree);
	}
	return (NULL);
}

t_tree		*ft_pars_red(t_tok *token, int start, int end)
{
	t_tree	*tree;

	if ((tree = ft_red_right(token, start, end, REL)))
		return (tree);
	else if ((tree = ft_red_right(token, start, end, RER)))
		return (tree);
	return (NULL);
}
