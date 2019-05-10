/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_environ_aux_functions.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 00:54:15 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/27 15:14:54 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	This function returns a pointer to an environment variable (key)'s value
**	For instance, if the envrionment is defined like follows:
**	[0]=>HOME=/tmp || [1]=>PWD=/home || [2]=>NULL
**							   ^
**	Then the call ft_get_env_var(env, "PWD") will return a pointer to string
**	following the first '=' sign of the 'PWD' variable
**	NOTE: This function DOES NOT allocate memory nor does it duplicate the
**	matching string. Therefore the returned pointer SHOULD NOT be freed
**	Also, this function saves the 'environ' array in a static reference
**	In case said array is NULL, it shall be replaced by the function's static
**	value
**	This allows to get environment values from anywhere in the code without
**	having an actual reference to the environment array to pass as parameter
**
**	Arguments:
**	environ -> The environment array
**	key -> The variable's name to look for
**
**	Return Value:
**	NULL -> No matching string was found in the 'environ' array
**	Otherwise, a pointer to the variable's value (after the first '=' sign)
*/

char	*utility_get_env_var(char ***environ, char *key)
{
	int			i;
	size_t		key_len;
	static char	***internal_reference = NULL;

	if (environ == NULL)
		environ = internal_reference;
	i = -1;
	key_len = ft_strlen(key);
	internal_reference = environ;
	while (environ && *environ && (*environ)[++i] != NULL)
	{
		if (ft_strncmp(key, (*environ)[i], key_len) == 0
			&& (*environ)[i][key_len] == '=')
			return (ft_strchr((*environ)[i], '=') + 1);
	}
	return (NULL);
}

/*
**	This functions returns the number of elements contained in
**	the shell's environment array (NULL not included)
**	Hence its 'length'
**
**	Arguments:
**	tab -> The shell's environment array
**
**	Return Value:
**	(-1) -> Error: the environment is NULL
**	Otherwise the actual length of the shell's environment
*/

int		utility_get_environ_length(char **tab)
{
	int	res;

	if (tab == NULL)
		return (-1);
	res = 0;
	while (tab[res] != NULL)
		res++;
	return (res);
}
