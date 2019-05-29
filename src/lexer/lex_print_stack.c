/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_print_stack.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 10:11:50 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/29 09:12:28 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

void		lex_print_stack(t_st *stack)
{
	if (!stack)
		return ;
	ft_print_stat_fd(stack->elmt, 1);
	if (stack->next)
		ft_putstr(">  <");
	lex_print_stack(stack->next);
}
