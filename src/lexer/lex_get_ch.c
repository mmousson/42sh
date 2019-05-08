/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 14:54:33 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/02 21:09:15 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

int					ft_get_ch(char c)
{
	static char		line[13] = "<>\"'&\\$~|;-/\n";
	int				k;

	if (c == 0)
		return (ZER);
	else if (c >= '0' && c <= '9')
		return (INT);
	else if (c == ' ' || c == '\t')
		return (SPA);
	k = -1;
	while (++k < 13)
		if (c == line[k])
			return (k + 4);
	return (CHA);
}
