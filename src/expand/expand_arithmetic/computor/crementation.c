/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crementation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 17:42:09 by hben-yah          #+#    #+#             */
/*   Updated: 2019/05/28 17:49:28 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "arithmetic.h"
#include "libft.h"

int		compute_crementation(char ***env, t_arithast *ast, long *res)
{
	long	a;
	char	*val;

	a = 0;
	if (ast->left)
	{
		if (compute_variable(env, ast->left, &a))
			return (1);
		*res = (ast->token->type == DOUBLEPLUS ? a++ : a--);
		if (!(val = ft_ltoa(*res)))
			return (1);
		utility_set_var(ast->left->token->val, val, env, 0);
	}
	else if (ast->right)
	{
		if (compute_variable(env, ast->right, &a))
			return (1);
		*res = (ast->token->type == DOUBLEPLUS ? ++a : --a);
		if (!(val = ft_ltoa(*res)))
			return (1);
		utility_set_var(ast->right->token->val, val, env, 0);
	}
	return (0);
}