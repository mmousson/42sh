/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_red.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 14:59:06 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/15 16:59:05 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"
#include "libft.h"

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
		if (!(tree->right = ft_pars_pipe(token, pos2, end)))
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
