/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:03:50 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/09 12:48:30 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

static int	is_bs_to_store(t_stat *stat, char **str)
{
	char	c;

	if (!str || !(*str) || !(*str)[stat->k])
		return (1);
	if (stat->old_status == BS && (*str)[stat->k] == '\n')
		return (0);
	c = (*str)[stat->k + 1];
	if (stat->status == BS && (!c || c == '\n'))
		return (0);
	return (1);
}

static void	validate_new_old(t_stat *stat, char buff[BUF], t_tok **tok)
{
	lex_add_char(buff, &(stat->load), stat->cha);
	if (stat->status == VO)
		stat->ch = stat->old_status;
	lex_add_tok(buff, stat->load, stat->ch, *tok);
	stat->status = 0;
}

int			lex_proc(t_stat *stat, char buff[BUF], t_tok **tok, char **str)
{
	int		ret;

	if (stat->status == VS)
	{
		(stat->k)--;
		lex_add_tok(buff, stat->load, stat->old_status, *tok);
		stat->status = 0;
	}
	else if (stat->status == VA || stat->status == VO)
		validate_new_old(stat, buff, tok);
	else if (stat->status == SK || stat->status == US)
		return (lex_store(stat, buff));
	else if (stat->status == SD && lex_store_dol(stat, buff, str))
		return (0);
	else if (stat->status == MO)
		return (-1);
	else if (stat->status == DB && !lex_back_slash_quote(stat, str, buff))
		return (0);
	else if (stat->status == ML && (ret = lex_exclam(stat, tok, str, buff)))
		return (ret);
	else if (stat->status != EN && is_bs_to_store(stat, str))
		lex_add_char(buff, &(stat->load), stat->cha);
	return (0);
}
