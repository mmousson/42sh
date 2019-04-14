/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 14:10:42 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/14 15:38:18 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"

t_hash	g_hash[HASH_MOD];

void	init_hash_table(void)
{
	int	i;

	i = -1;
	while (++i < HASH_MOD)
	{
		g_hash[i].full_path = NULL;
		g_hash[i].next = NULL;
	}
}

int		hash(int argc, char **argv, char ***env)
{

}
