/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_is_delimiter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 17:45:29 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/28 18:10:49 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"
#define SIZE 4

int				pars_is_delimiter(int status)
{
	int			k;
	static int	tab[SIZE] = {
		SMC, ESP, ESP + DBL, PIP + DBL
	};

	k = -1;
	while (++k < SIZE)
		if (status == tab[k])
			return (1);
	return (0);
}
