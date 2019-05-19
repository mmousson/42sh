/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_get_ch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:04:37 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/19 15:06:12 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#define F_STAT 3

int					lex_get_ch(char c)
{
	static char		line[NB_CH - F_STAT] = "<>\"'(&\\|;\n)!$";
	int				k;

	if (c == 0)
		return (ZER);
	else if (c == ' ' || c == '\t')
		return (SPA);
	k = -1;
	while (++k < NB_CH - F_STAT)
		if (c == line[k])
			return (k + F_STAT);
	return (CHA);
}
