/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 17:57:48 by oboutrol          #+#    #+#             */
/*   Updated: 2019/04/30 20:04:28 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"
#include <stdlib.h>

void		*ft_free_tree(t_tree *tree)
{
	if (!tree)
		return (NULL);
	ft_free_tree(tree->right);
	tree->right = NULL;
	ft_free_tree(tree->left);
	tree->left = NULL;
	if (tree->content)
		free(tree->content);
	free(tree);
	return (NULL);
}
