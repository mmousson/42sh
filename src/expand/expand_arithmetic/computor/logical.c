/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 17:42:09 by hben-yah          #+#    #+#             */
/*   Updated: 2019/05/28 16:45:59 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arithmetic.h"

int		compute_logical(char ***env, char *exp, t_arithast *ast, long *res)
{
	if (compute(env, exp, ast->left, res))
		return (1);
	if ((ast->token->type == DOUBLEPIPE && (*res = (*res != 0)))
		|| (ast->token->type == DOUBLEAND && !(*res = (*res != 0))))
		return (0);
	if (compute(env, exp, ast->right, res))
		return (1);
	*res = (*res != 0);
	return (0);
}

int		compute_inverse(char ***env, char *exp, t_arithast *ast, long *res)
{
	if (compute(env, exp, ast->right, res))
		return (1);
	*res = !*res;
	return (0);
}
