/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_internal_var_exists.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 05:49:15 by mmousson          #+#    #+#             */
/*   Updated: 2019/05/14 07:29:45 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh42.h"

/*
**	This functions tells whether an internal variable 'name' exists in the
**	current shell internal variables list
**
**	Arguments:
**	name -> The variable name to look for
**
**	Return Value:
**	NULL -> The internal variable 'name' doesn't exist
**	NON_NULL -> The internal variable 'name' exists
*/

char	*utility_internal_var_exists(char *name, t_vars **holder)
{
	t_vars	*current;

	current = g_shell_var_list;
	while (current)
	{
		if (ft_strequ(name, current->name))
		{
			if (holder != NULL)
				*holder = current;
			return (current->value);
		}
		current = current->next;
	}
	return (NULL);
}
