/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 12:12:17 by roliveir          #+#    #+#             */
/*   Updated: 2019/03/03 12:46:02 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_getenv(char **env, char *name)
{
	int			i;
	int			j;

	i = -1;
	j = 0;
	if (!name)
		return (NULL);
	while (env[++i])
	{
		if (!ft_strncmp(env[i], name, ft_strlen(name)))
		{
			while (env[i][j] && env[i][j] != '=')
				j++;
			if (env[i][j])
				return (ft_strdup(&env[i][++j]));
		}
	}
	return (NULL);
}
