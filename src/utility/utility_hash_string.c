/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_hash_string.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 13:18:18 by mmousson          #+#    #+#             */
/*   Updated: 2019/05/13 21:41:39 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh42.h"

/*
**	This function generates a hash of a string
**	Needed by the 'hash' builtin
**	The idea is to add the 1-based alphabetical value of each character
**	mutliplied by their respective rank in the string, raised to
**	the power 'HASH_POWER'
**	This method demonstrated no collision so far with the 2245 binaries present
**	in the system
**	Although, if the user were to add a lot of binaries to the PATH, collisions
**	are bound to happen
**	Collision-resolution technique is explained in the file
**	'builtins/hash/add_hash_entry.c'
**
**	Arguments:
**	string -> The string to hash
**
**	Return Value:
**	The computed hash of the provided string
*/

int	hash_string(char *string)
{
	const int	power = HASH_POWER;
	const int	mod = HASH_MOD;
	int			result;
	int			current_power;;
	int			i;

	if (string == NULL)
		return (0);
	i = -1;
	result = 0;
	current_power = 1;
	while (string[++i] != '\0')
	{
		if (string[i] >= 'a' && string[i] <= 'z')
			result = (result + (string[i] - 'a' + 1) * current_power) % mod;
		current_power = (current_power * power) % mod;
	}
	return (result);
}
