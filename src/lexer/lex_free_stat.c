/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_free_stat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:49:29 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/29 09:26:06 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

static void	lex_free_stack(t_st *stack)
{
	if (!stack)
		return ;
	lex_free_stack(stack->next);
	stack->next = NULL;
	free(stack);
}

void		lex_free_stat(t_stat *stat)
{
	if (!stat)
		return ;
	if (stat->load)
	{
		free(stat->load);
		stat->load = NULL;
	}
	if (stat->stack)
	{
		lex_free_stack(stat->stack);
		stat->stack = NULL;
	}
	free(stat);
}
