/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hash_table.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 22:24:20 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/15 23:15:08 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh42.h"

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
