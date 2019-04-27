/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_builtins_utility.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 11:51:53 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/27 15:09:27 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh42.h"

/*
**	Put together all the builtins functions in a single table
**	Builtins prototype are delcared in includes/sh42.h
*/

t_builtins	g_builtins[] = {
	{"alias", &blt_alias},
	{"bg", &blt_bg},
	{"cd", &blt_cd},
	{"echo", &blt_echo},
	{"exit", &blt_exit},
	{"export", &blt_export},
	{"fg", &blt_fg},
	{"hash", &blt_hash},
	{"jobs", &blt_jobs},
	{"set", &blt_set},
	{"test", &blt_test},
	{"type", &blt_type},
	{"unalias", &blt_unalias},
	{"unset", &blt_unset},
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

int	utility_is_builtin(char *name)
{
	int			i;
	t_builtins	*ptr;

	i = 0;
	ptr = g_builtins;
	while (ptr->name != NULL)
	{
		if (ft_strequ(name, ptr->name))
			return (i);
		ptr++;
		i++;
	}
	return (-1);
}
