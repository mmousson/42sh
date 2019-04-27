/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 16:16:51 by oboutrol          #+#    #+#             */
/*   Updated: 2019/04/06 21:36:59 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

int		proc(t_stat *stat, char buff[BUF], t_tok *tok)
{
	if (stat->status == VS)
	{
		(stat->k)--;
		ft_add_token(buff, stat->load, stat->old_status, tok);
		stat->status = 0;
	}
	else if (stat->status == VA)
	{
		ft_add_char(buff, &(stat->load), stat->cha);
		ft_add_token(buff, stat->load, stat->ch, tok);
		stat->status = 0;
	}
	else if (stat->status == SV)
	{
		ft_add_token(buff, stat->load, stat->ch, tok);
		stat->status = 0;
	}
	else if (stat->status == DS)
		stat->status = DQ;
	else if (stat->status == SS)
		stat->status = SQ;
	else if (stat->status == MO)
		return (-1);
	else if (stat->status != EN && stat->status != BS)
		ft_add_char(buff, &(stat->load), stat->cha);
	return (0);
}
