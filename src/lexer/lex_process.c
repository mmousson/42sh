/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:03:50 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/11 18:50:13 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

int		lex_proc(t_stat *stat, char buff[BUF], t_tok **tok, char **str)
{
	if (stat->status == VS)
	{
		(stat->k)--;
		lex_add_tok(buff, stat->load, stat->old_status, *tok);
		stat->status = 0;
	}
	else if (stat->status == VA || stat->status == SV)
	{
		if (stat->status == VA)
			lex_add_char(buff, &(stat->load), stat->cha);
		lex_add_tok(buff, stat->load, stat->ch, *tok);
		stat->status = 0;
	}
	else if (stat->status == DS)
		stat->status = DQ;
	else if (stat->status == SS)
		stat->status = SQ;
	else if (stat->status == MO)
		return (-1);
	else if (stat->status == ML && !lex_exclam(stat, tok, str))
		return (0);
	else if (stat->status != EN && stat->status != BS)
		lex_add_char(buff, &(stat->load), stat->cha);
	return (0);
}
