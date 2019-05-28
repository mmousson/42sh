/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sub_expression.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 17:42:09 by hben-yah          #+#    #+#             */
/*   Updated: 2019/05/28 14:35:29 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arithmetic.h"

int		check_is_sub_expression(t_arithtok **tok)
{
	t_arithtok *b;

	if (!*tok)
		return (0);
	b = *tok;
	if (check_token(tok, OP_PAR)
		&& !check_is_expression(tok)
		&& check_token(tok, CL_PAR))
		return (1);
	*tok = b;
	return (0);
}
