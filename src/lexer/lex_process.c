/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:03:50 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/15 19:28:27 by oboutrol         ###   ########.fr       */
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

static int	validate_new_old(t_stat *stat, char buff[BUF], char **str)
{
	lex_add_char(buff, &(stat->load), stat->cha);
	if (stat->status == VO)
		stat->ch = stat->old_status;
	if (lex_add_tok(buff, stat, stat->ch, str))
		return (1);
	stat->status = 0;
	return (0);
}

static int	validate(char buff[BUF], t_stat *stat, char **str)
{
	(stat->k)--;
	if (lex_add_tok(buff, stat, stat->old_status, str))
		return (1);
	stat->status = 0;
	return (0);
}

int			lex_proc(t_stat *stat, char buff[BUF], char **str)
{
	if (stat->status == VS)
	{
		if (validate(buff, stat, str))
			return (1);
	}
	else if (stat->status == VA || stat->status == VO)
	{
		if (validate_new_old(stat, buff, str))
			return (1);
	}
	else if (stat->status == SK || stat->status == US)
		return (lex_store(stat, buff));
	else if (stat->status == SD && lex_store_dol(stat, buff, str))
		return (0);
	else if (stat->status == MO)
		return (-1);
	else if (stat->status == DB && !lex_back_slash_quote(stat, str, buff))
		return (0);
	else if (stat->status != EN && is_bs_to_store(stat, str))
		lex_add_char(buff, &(stat->load), stat->cha);
	return (0);
}
