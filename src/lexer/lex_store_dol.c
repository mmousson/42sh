/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_store_dol.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 12:01:16 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/19 15:31:40 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

int			lex_store_dol(t_stat *stat, char buff[BUF], char **str)
{
	char	next_char;

	next_char = (*str)[stat->k + 1];
	if (next_char == '(')
	{
		lex_add_char(buff, &(stat->load), stat->cha);
		stat->k += 1;
		lex_step(&stat, str);
		lex_pile_up(stat, buff);
	}
	else
	{
		stat->status = CHA;
		return (0);
	}
	stat->status = lex_last_pile(stat);
	ft_putstr("current pile: ");lex_print_stack(stat->stack);ft_putchar('\n');
	return (1);
}
