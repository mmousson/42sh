/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_get_param.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 19:53:56 by mmousson          #+#    #+#             */
/*   Updated: 2019/05/25 07:54:29 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sh42.h"

/*
**	Wrapper function to get the value of a variable in either:
**		-> Reserved variables
**		-> Environment variables
**		-> Internal variables
**
**	Arguments:
**	key -> The name of the variable we want to obtain
**	env -> The shell's current environment definition
**
**	Return Value:
**	NULL -> The variable identitfied by 'key' doesn't exist
**	NON-NULL -> The variable identified by 'key' exists and its value is
**		is returned in a newly allocated area
*/

char	*utility_get_param(char *key, char **env)
{
	int		id;

	if (key == NULL)
		return (NULL);
	if ((key[0] != '\0' && key[1] == '\0'
		&& (id = core_hash_spec_var(key[0])) != -1))
		return (core_spec_var_setget(id, NULL, GET));
	else
		return (utility_get_var(key, env));
}
