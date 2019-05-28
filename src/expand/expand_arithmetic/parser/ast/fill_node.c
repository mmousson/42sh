/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 17:42:09 by hben-yah          #+#    #+#             */
/*   Updated: 2019/05/28 14:36:41 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arithmetic.h"
#include "libft.h"

int
	arith_fill_node(t_arithast **ast, t_arithtok **chosen)
{
	if (!(*ast = (t_arithast *)ft_memalloc(sizeof(t_arithast))))
		return (1);
	(*ast)->token = token_dup(*chosen);
	token_del(chosen);
	return (0);
}
