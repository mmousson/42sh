/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:03:50 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/19 15:06:13 by oboutrol         ###   ########.fr       */
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
	else if (stat->status == VA)
	{
		lex_add_char(buff, &(stat->load), stat->cha);
		lex_add_tok(buff, stat->load, stat->ch, *tok);
		stat->status = 0;
	}
	else if (stat->status == SK || stat->status == US)
		return (lex_store(stat, buff));
	else if (stat->status == SD && lex_store_dol(stat, buff, str))
		return (0);
	else if (stat->status == MO)
		return (-1);
	else if (stat->status == DB && !lex_back_slash_quote(stat, str, buff))
		return (0);
	else if (stat->status == ML && !lex_exclam(stat, tok, str))
		return (0);
	else if (stat->status != EN && stat->status != BS)
		lex_add_char(buff, &(stat->load), stat->cha);
	return (0);
}
