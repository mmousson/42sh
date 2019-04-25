/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_aux_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 00:54:15 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/25 03:05:11 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**
*/

char	*ft_get_env_var(char ***environ, char *key)
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
**
*/

int		ft_get_environ_length(char **tab)
{
	int	res;

	if (tab == NULL)
		return (-1);
	res = 0;
	while (tab[res] != NULL)
		res++;
	return (res);
}
