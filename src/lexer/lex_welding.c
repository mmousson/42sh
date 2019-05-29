/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_welding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 21:24:13 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/28 21:48:32 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

int		lex_welding(t_stat *stat)
{
	if (stat->ch == CBO)
		stat->ch = PAO;
	else if (stat->ch == CBC)
		stat->ch = PAC;
	return (1);
}
