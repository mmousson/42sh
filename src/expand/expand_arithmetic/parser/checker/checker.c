/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 17:42:09 by hben-yah          #+#    #+#             */
/*   Updated: 2019/05/28 17:52:06 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arithmetic.h"
#include "libft.h"
#include "sh42.h"

int			arith_div_zero_error(char *expr, t_arithtok *tok)
{
	if (expr)
	{
		ft_putstr2_fd(""SH_NAME": ", expr, 2);
		ft_putstr_fd(": division by 0 (error token is \"", 2);
		ft_putendl2_fd(&tok->val[tok->length - 1], "\")\n", 2);
	}
	return (1);
}

int			arith_value_base_error(t_arithtok *begin, t_arithtok *tok)
{
	ft_putstr_fd(""SH_NAME": ", 2);
	while (begin && begin != tok)
	{
		ft_putstr2_fd(begin->val, (begin->next ? " " : ""), 2);
		begin = begin->next;
	}
	ft_putstr_fd(": value too great for base (error token is \"", 2);
	ft_putendl2_fd(tok->val, "\")\n", 2);
	return (1);
}

int			arith_syntax_error(char *expr, t_arithtok *tok, int err)
{
	if (expr)
	{
		ft_putstr3_fd(""SH_NAME": ", expr, ": syntax error", 2);
		ft_putstr2_fd((err == 2 ? " in expression" : ": operand expected"),
			" (error token is \"", 2);
		while (tok && tok->val)
		{
			ft_putstr2_fd(tok->val, (tok->next ? " " : ""), 2);
			tok = tok->next;
		}
		ft_putendl_fd("\")\n", 2);
	}
	return (258);
}

t_arithtok	*check_expression_lex(t_arithtok *token, int *err)
{
	t_arithtok *t;

	if (!token)
		return (NULL);
	t = token;
	if ((*err = check_is_expression(&t)))
		return (t);
	while (token && token->valid)
	{
		if (token->type == NUMBER && token->valid == INVALID)
		{
			*err = 3;
			return (token);
		}
		token = token->next;
	}
	return (token);
}

int			check_expression(char *expr, t_arithtok *token)
{
	t_arithtok	*error_tok;
	int			err;
	char		*val;

	if (!token)
		return (0);
	err = 0;
	if ((error_tok = check_expression_lex(token, &err)) || err)
	{
		if (err == 3)
			val = ft_itoa(arith_value_base_error(token, error_tok));
		else
			val = ft_itoa(arith_syntax_error(expr, error_tok, err));
		if (!val)
			return (1);
		core_spec_var_setget(10, val, SET);
		return (1);
	}
	return (0);
}
