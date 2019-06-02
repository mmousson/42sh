/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_store_dol.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 12:01:16 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/31 15:33:16 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

int			lex_store_dol(t_stat *stat, char buff[BUF], char **str)
{
	char	next_char;

	next_char = (*str)[stat->k + 1];
	if (ft_strchr("({", next_char))
	{
		lex_add_char(buff, &(stat->load), stat->cha);
		stat->k += 1;
		lex_step(&stat, str);
		lex_pile_up(stat, buff);
		return (1);
	}
	stat->status = lex_last_pile(stat);
	return (0);
}
