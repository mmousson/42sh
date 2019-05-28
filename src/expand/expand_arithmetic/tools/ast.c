/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 16:03:42 by hben-yah          #+#    #+#             */
/*   Updated: 2019/05/28 17:45:52 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arithmetic.h"
#include "libft.h"

void	astlist_del(t_arithast **ast)
{
	if (ast && *ast)
	{
		if ((*ast)->right)
			astlist_del(&(*ast)->right);
		if ((*ast)->right_arg)
			tokenlist_del(&(*ast)->right_arg);
		if ((*ast)->token)
			tokenlist_del(&(*ast)->token);
		if ((*ast)->left_arg)
			tokenlist_del(&(*ast)->left_arg);
		if ((*ast)->left)
			astlist_del(&(*ast)->left);
		ft_memdel((void **)ast);
	}
}
