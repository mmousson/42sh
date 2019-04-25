/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_nword.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 18:58:08 by oboutrol          #+#    #+#             */
/*   Updated: 2019/04/13 07:35:44 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"
#include <stdlib.h>
#include "libft.h"
#include <unistd.h>

t_tree		*ft_pars_nword(t_tok *token, int start, int end)
{
	t_tok	*tok;
	t_tree	*tree;

	tok = ft_go_start(token, start);
	if (tok == NULL || (start > end && end != -2))
		return (NULL);
	if ((tree = ft_pars_part(token, start, end)))
		return (tree);
	else
	{
		if (!(tree = ft_end_branch()))
			return (NULL);
		if (!(tree->left = ft_pars_part(token, start, start)))
			return (NULL);
		if (!(tree->right = ft_pars_nword(token, start + 1, end)))
			return (NULL);
		return (tree);
	}
	return (NULL);
}
