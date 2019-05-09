/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_free_stat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:49:29 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/09 15:52:51 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include <stdlib.h>

void		lex_free_stat(t_stat *stat)
{
	if (!stat)
		return ;
	if (stat->load)
	{
		free(stat->load);
		stat->load = NULL;
	}
	free(stat);
}
