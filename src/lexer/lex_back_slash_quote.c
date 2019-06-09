/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_back_slash_quote.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 14:40:24 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/09 12:49:20 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

int			lex_back_slash_quote(t_stat *stat, char **str, char buff[BUF])
{
	char	escap;

	escap = (*str)[stat->k + 1];
	if (!(escap || escap == '\n') && lex_more(stat, str, 0, 0))
	{
		(stat->k)++;
		return (0);
	}
	else if (escap == '"' || escap == '\\')
	{
		lex_add_char(buff, &(stat->load), '\\');
		lex_add_char(buff, &(stat->load), escap);
		stat->status = DQ;
		(stat->k)++;
		return (0);
	}
	else
		stat->status = DQ;
	return (1);
}
