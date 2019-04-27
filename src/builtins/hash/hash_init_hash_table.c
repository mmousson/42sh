/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hash_table.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 22:24:20 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/16 00:04:42 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh42.h"

/*
**	This function is used to initialize the struct array 'g_hash' to 0
**	on bootup (called by main)
**
**	Arguments: NONE
**
**	Return Value: NONE
*/

void		init_hash_table(void)
{
	int	i;

	i = -1;
	while (++i < HASH_MOD)
	{
		g_hash[i].hits = 0;
		g_hash[i].full_path = NULL;
		g_hash[i].next = NULL;
	}
}
