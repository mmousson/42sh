/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 13:22:34 by oboutrol          #+#    #+#             */
/*   Updated: 2019/04/08 13:45:21 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"
#include <stdlib.h>

t_tree		*ft_end_branch(void)
{
	t_tree	*new;

	if (!(new = (t_tree*)malloc(sizeof(t_tree))))
		return (NULL);
	new->right = NULL;
	new->left = NULL;
	new->type = ZER;
	new->content = NULL;
	return (new);
}
