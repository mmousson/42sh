/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 13:18:18 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/14 15:13:27 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	This function generates a hash of a string
**	Needed by the 'hash' builtin
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
		result = (result + (string[i] - 'a' + 1) * current_power) % mod;
		current_power = (current_power * power) % mod;
	}
	return (result);
}
