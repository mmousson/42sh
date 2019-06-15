/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_get_ch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:04:37 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/14 15:21:55 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#define F_STAT 3

int					lex_get_ch(char c)
{
	static char		line[NB_CH - F_STAT] = "<>\"'(&\\|;)!$";
	int				k;

	if (c == 0)
		return (ZER);
	else if (c == ' ' || c == '\t')
		return (SPA);
	else if (c == '\n')
		return (SMC);
	k = -1;
	while (++k < NB_CH - F_STAT)
		if (c == line[k])
			return (k + F_STAT);
	if (c == '{')
		return (PAO);
	else if (c == '}')
		return (PAC);
	return (CHA);
}

int					get_sub_type(int stat)
{
	static int		mat_type[NB_CH] = {
		EROR, CHAR, SPAC, REDI, REDI,
		CHAR, CHAR, CHAR, SMCL, CHAR,
		PIPE, SMCL, CHAR, CHAR, CHAR,
		CHAR, CHAR
	};

	if (stat >= NB_CH || stat < 0)
		return (EROR);
	return (mat_type[stat]);
}

int					ft_get_type(t_tok *token)
{
	int				stat;

	if (!token)
		return (ENDT);
	stat = token->status;
	return (get_sub_type(stat));
}
