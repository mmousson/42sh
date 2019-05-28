/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_operande.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 17:42:09 by hben-yah          #+#    #+#             */
/*   Updated: 2019/05/28 14:35:37 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arithmetic.h"

int		check_is_operande(t_arithtok **tok)
{
	t_arithtok *b;
	t_arithtok *c;

	if (!*tok)
		return (0);
	b = *tok;
	check_token(tok, BANG);
	while ((c = *tok)
		&& (check_token(tok, PLUS) || check_token(tok, MINUS)))
		;
	*tok = c;
	if (check_is_number(tok))
		return (1);
	*tok = c;
	if (check_is_variable(tok))
		return (1);
	*tok = c;
	if (check_is_sub_expression(tok))
		return (1);
	*tok = b;
	return (0);
}
