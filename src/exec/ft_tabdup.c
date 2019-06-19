/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 08:57:03 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/10 13:40:17 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				**ft_tabdup(char **tab)
{
	int				k;
	char			**dup;

	if (!tab)
		return (NULL);
	k = 0;
	while (tab[k])
		k++;
	if (!(dup = (char**)malloc(sizeof(char*) * (k + 1))))
		return (NULL);
	dup[k] = 0;
	while (--k >= 0)
	{
		if (!(dup[k] = ft_strdup(tab[k])))
		{
			ft_del_words_tables(&dup);
			return (NULL);
		}
	}
	return (dup);
}
