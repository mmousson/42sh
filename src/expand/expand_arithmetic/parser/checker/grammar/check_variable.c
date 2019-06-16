/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 17:42:09 by hben-yah          #+#    #+#             */
/*   Updated: 2019/06/16 17:34:31 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arithmetic.h"

int		check_is_variable(t_arithtok **tok)
{
	t_arithtok	*b;
	int			i;

	if (!*tok)
		return (0);
	b = *tok;
	i = (check_token(tok, DOUBLEPLUS) || check_token(tok, DOUBLEMINUS));
	if (check_token(tok, VARIABLE))
	{
		if (i == 0)
		{
			if (!check_token(tok, DOUBLEPLUS))
				check_token(tok, DOUBLEMINUS);
		}
		return (1);
	}
	*tok = b;
	return (0);
}
