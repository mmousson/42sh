/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utility.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 11:51:53 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/25 05:47:46 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh42.h"

/*
**	Put together all the builtins functions in a single table
**	Builtins prototype are delcared in includes/sh42.h
*/

t_builtins	g_builtins[] = {
	{"alias", &alias},
	{"bg", &bg},
	{"cd", &cd},
	{"echo", &echo},
	{"exit", &ft_exit},
	{"export", &ft_export},
	{"fg", &fg},
	{"hash", &hash},
	{"jobs", &jobs},
	{"set", &set},
	{"test", &ft_test},
	{"type", &type},
	{"unalias", &unalias},
	{"unset", &unset},
	{NULL, NULL}
};

/*
**	This function checks if a Builtin Name actually exists by searching for
**	a match in the lookup table above
**	If the provided 'name' indeed is builtin command, return (1), otherwise (0)
**
**	Arguments:
**	name -> The builtin name to search a match for
**
**	Return Value:
**	0 -> The builtin doesn't exist
**	1 -> The builtin exists
*/

int	is_builtin(char *name)
{
	t_builtins	*ptr;

	ptr = g_builtins;
	while (ptr->name != NULL)
	{
		if (ft_strequ(name, ptr->name))
			return (1);
		ptr++;
	}
	return (0);
}
