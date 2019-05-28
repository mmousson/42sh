/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 17:42:09 by hben-yah          #+#    #+#             */
/*   Updated: 2019/05/28 16:46:19 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arithmetic.h"

int		compute_operation(char ***env, char *exp, t_arithast *ast, long *res)
{
	long	a;

	a = 0;
	if (compute(env, exp, ast->left, res)
			|| compute(env, exp, ast->right, &a))
		return (1);
	if (ast->token->type == PLUS)
		*res += a;
	else if (ast->token->type == MINUS)
		*res -= a;
	else if (ast->token->type == STAR)
		*res *= a;
	else if (ast->token->type == DOUBLEEQUAL)
		*res = (*res == a);
	else if (ast->token->type == BANGEQUAL)
		*res = (*res != a);
	else if (ast->token->type == LESS)
		*res = (*res < a);
	else if (ast->token->type == GREAT)
		*res = (*res > a);
	else if (ast->token->type == GREATEQUAL)
		*res = (*res >= a);
	else if (ast->token->type == LESSEQUAL)
		*res = (*res <= a);
	return (0);
}

int		compute_division(char ***env, char *exp, t_arithast *ast, long *res)
{
	long	a;

	a = 0;
	if (compute(env, exp, ast->left, res)
		|| compute(env, exp, ast->right, &a) || (a == 0))
		return (arith_div_zero_error(exp, ast->right->token));
	if (ast->token->type == SLASH)
		*res /= a;
	else if (ast->token->type == PERCENT)
		*res %= a;
	return (0);
}
