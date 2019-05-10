/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_exists.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 11:24:57 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/14 11:30:36 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh42.h"

/*
**	This function checks if an alias definition identified by 'token' exists
**	in the current shell execution environment
**	It does that by looping through the entine alias list and returning the
**	replacement string when a match is found
**	If no match is found, return (NULL)
**
**	Arguments:
**	token -> The ID of the alias definiton to look for
**
**	Return Value:
**	(NULL) -> No match has been found
**	(NON-NULL) -> Alias exists and the replacement token is returned
*/

char	*alias_exists(char *token)
{
	t_alias	*current;

	current = alias_list;
	while (current)
	{
		if (ft_strequ(current->token, token))
			return (current->replacement);
		current = current->next;
	}
	return (NULL);
}
