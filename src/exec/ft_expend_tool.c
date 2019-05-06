/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expend_tool.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:56:37 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/06 22:05:11 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"
#include "exe.h"
#include "libft.h"
#include <stdlib.h>

int		is_clean(int val)
{
	if (val == CHA || val == INT || val == DQT || val == SQT || val == ESP)
		return (1);
	return (0);
}

char	*ft_doll(t_tree *tree, char **arge)
{
	if (!tree || !tree->content || !tree->content[0] || !tree->content[1])
		return (NULL);
	return (ft_getenv(arge, &tree->content[1]));
}
