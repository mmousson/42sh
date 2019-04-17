/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 06:36:11 by oboutrol          #+#    #+#             */
/*   Updated: 2019/04/07 18:10:16 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexpars.h"
#include "libft.h"
#include <stdlib.h>
#include "built_in.h"

int				ft_fct(t_word *word, char **path, char **arge)
{
	int			k;

	if (!word || !word->value)
		return (-1);
	if ((k = ft_get_home_cmd(word->value)) >= 0)
		return (k);
	if (ft_path(word->value, path, arge))
		return (-2);
	return (-1);
}

int				ft_is_fct(char *name, char **arge)
{
	char		*path;

	path = NULL;
	if (!name)
		return (0);
	if (ft_get_home_cmd(name) >= 0)
		return (1);
	if (ft_path(name, &path, arge))
	{
		if (path)
			free(path);
		return (1);
	}
	if (path)
		free(path);
	return (0);
}
