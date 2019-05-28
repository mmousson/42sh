/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 18:41:25 by hben-yah          #+#    #+#             */
/*   Updated: 2019/05/28 16:53:45 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arithmetic.h"

int		check_token(t_arithtok **tok, int type)
{
	if (!*tok)
		return (0);
	if ((*tok)->type == type)
	{
		(*tok)->valid = type;
		*tok = (*tok)->next;
		return (1);
	}
	return (0);
}
