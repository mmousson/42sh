/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_get_ch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:04:37 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/10 09:32:49 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

int					lex_get_ch(char c)
{
	static char		line[15] = "<>\"'&\\$~|;-/\n()";
	int				k;

	if (c == 0)
		return (ZER);
	else if (c >= '0' && c <= '9')
		return (INT);
	else if (c == ' ' || c == '\t')
		return (SPA);
	k = -1;
	while (++k < 15)
		if (c == line[k])
			return (k + 4);
	return (CHA);
}
