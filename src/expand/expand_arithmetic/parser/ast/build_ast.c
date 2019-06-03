/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 17:42:09 by hben-yah          #+#    #+#             */
/*   Updated: 2019/06/03 17:43:56 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arithmetic.h"

static int
	arith_add_node(t_arithast **ast, t_arithtok *beginlist)
{
	t_arithtok	*chosen_prev;
	t_arithtok	*chosen;

	if (!ast || !beginlist)
		return (0);
	arith_remove_parentheses(&beginlist);
	chosen_prev = NULL;
	if (!(chosen = arith_get_primary_prev_token(&chosen_prev, beginlist)))
		return (0);
	if (chosen_prev)
		chosen_prev->next = NULL;
	else
		beginlist = NULL;
	if (arith_fill_node(ast, &chosen))
		return (1);
	if ((beginlist && arith_add_node(&(*ast)->left, beginlist))
		|| (chosen && arith_add_node(&(*ast)->right, chosen)))
		return (1);
	return (0);
}

int
	arith_build_ast(t_arithast **ast, t_arithtok **token)
{
	if (token && *token && arith_add_node(ast, *token))
	{
		astlist_del(ast);
		return (1);
	}
	*token = NULL;
	return (0);
}
