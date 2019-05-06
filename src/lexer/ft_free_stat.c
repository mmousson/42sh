/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_stat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 20:11:57 by oboutrol          #+#    #+#             */
/*   Updated: 2019/04/30 20:25:11 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include <stdlib.h>

void		ft_free_stat(t_stat *stat)
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
