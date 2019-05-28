/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_arithmetic.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 17:42:09 by hben-yah          #+#    #+#             */
/*   Updated: 2019/05/28 17:44:45 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arithmetic.h"
#include "libft.h"

int
	arithmetic(char ***env, long *res, char *str)
{
	t_arithtok		*tok;
	t_arithast		*ast;

	tok = NULL;
	ast = NULL;
	arith_lexical_analysis(&tok, str);
	*res = 0;
	if (!check_expression(str, tok))
	{
		if (arith_build_ast(&ast, &tok)
			|| compute(env, str, ast, res))
			return (1);
		astlist_del(&ast);
	}
	else
	{
		tokenlist_del(&tok);
		return (1);
	}
	return (0);
}

static int
	expand_arithmetic_one(char **str, char ***env)
{
	char		*beg;
	char		*end;
	long		res;

	while ((beg = ft_strstr(*str, "$(("))
		&& *(end = walkparenthese(beg + 2)))
	{
		ft_memset((void *)beg, 0, 3);
		ft_memset((void *)(end - 1), 0, 2);
		if (!(beg = ft_strdup(beg + 3)))
			return (1);
		if (expand_arithmetic_one(&beg, env))
			return (1);
		res = 0;
		if (arithmetic(env, &res, beg))
			return (1);
		ft_strdel(&beg);
		if (!(beg = ft_ltoa(res)))
			return (1);
		if (!(*str = ft_strjoin3fs(*str, beg, end + 1, FT_ARG1 | FT_ARG2)))
			return (1);
	}
	return (0);
}

int
	expand_arithmetic(char ***str, char ***env)
{
	int i;

	i = 0;
	while ((*str)[i])
	{
		if (expand_arithmetic_one(*str + i, env))
			return (1);
		++i;
	}
	return (0);
}
