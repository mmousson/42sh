/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 17:42:09 by hben-yah          #+#    #+#             */
/*   Updated: 2019/05/28 16:03:48 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arithmetic.h"

char	*walkparenthese(char *s)
{
	while (*s)
	{
		if (*s == '\\')
			++s;
		else if (*s == '(')
			s = walkparenthese(s + 1);
		else if (*s == ')')
			break ;
		*s && ++s;
	}
	return (s);
}

void	arith_remove_parentheses(t_arithtok **tok)
{
	t_arithtok *cur;

	if ((*tok)->type == OP_PAR)
	{
		cur = *tok;
		while (cur->next->next)
			cur = cur->next;
		if (cur && cur->next && cur->next->type == CL_PAR)
		{
			token_del(tok);
			token_del(&cur->next);
		}
	}
}
