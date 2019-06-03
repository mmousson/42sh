/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 17:42:09 by hben-yah          #+#    #+#             */
/*   Updated: 2019/06/03 17:19:10 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "arithmetic.h"
#include "libft.h"

int		compute_variable(char ***env, t_arithast *ast, long *res)
{
	char *val;

	val = utility_get_var(ast->token->val, *env);
	if (val ? arithmetic(env, res, val) : 0)
		return (1);
	return (0);
}

int		compute_number(t_arithast *ast, long *res)
{
	char *s;

	s = ast->token->val;
	if (*s == '0')
	{
		++s;
		if (*s == 'x' || *s == 'X')
			*res = ft_atol_base(++s, 16);
		else if (*s)
			*res = ft_atol_base(s, 8);
		else
			*res = 0;
		return (0);
	}
	*res = ft_atol_base(s, 10);
	return (0);
}

int		compute(char ***env, char *exp, t_arithast *ast, long *res)
{
	if (!ast)
		return (0);
	if (ast->token->type == NUMBER)
		return (compute_number(ast, res));
	if (ast->token->type == VARIABLE)
		return (compute_variable(env, ast, res));
	if (ast->token->type == SLASH
		|| ast->token->type == PERCENT)
		return (compute_division(env, exp, ast, res));
	if (ast->token->type == DOUBLEAND
		|| ast->token->type == DOUBLEPIPE)
		return (compute_logical(env, exp, ast, res));
	if (ast->token->type == DOUBLEPLUS
		|| ast->token->type == DOUBLEMINUS)
		return (compute_crementation(env, ast, res));
	if (ast->token->type == BANG)
		return (compute_inverse(env, exp, ast, res));
	return (compute_operation(env, exp, ast, res));
}
