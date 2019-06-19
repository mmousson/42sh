/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_alloc_space.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 14:25:05 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/25 14:32:48 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

char				*auto_alloc_name(char **str)
{
	int				i;
	char			*fresh;
	char			*tmp;

	i = -1;
	if (!(fresh = ft_strdup(*str)))
		sh_errorterm(TMALLOC);
	while (fresh[++i])
	{
		if (fresh[i] == ' ')
		{
			tmp = fresh;
			if (!(fresh = ft_strnew((int)ft_strlen(fresh) + 1)))
			{
				ft_strdel(&tmp);
				sh_errorterm(TMALLOC);
			}
			ft_strncpy(fresh, tmp, i);
			ft_strcpy(&(fresh[i]), "\\");
			ft_strcpy(&(fresh[i + 1]), &(tmp[i]));
			ft_strdel(&tmp);
			i++;
		}
	}
	return (fresh);
}
