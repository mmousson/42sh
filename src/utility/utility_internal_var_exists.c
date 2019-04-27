/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_var_exists.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 05:49:15 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/25 08:24:04 by mmousson         ###   ########.fr       */
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

char	*internal_var_exists(char *name)
{
	t_vars	*current;

	current = shell_var_list;
	while (current)
	{
		if (ft_strequ(name, current->name))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}
