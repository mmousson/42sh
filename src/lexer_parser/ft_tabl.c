/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 02:59:36 by oboutrol          #+#    #+#             */
/*   Updated: 2019/03/22 03:54:36 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexpars.h"
#include "libft.h"
#include <stdlib.h>

int			nb_chain(t_word *word)
{
	int		k;
	t_word	*tmp;

	if (!(word))
		return (0);
	k = 1;
	tmp = word;
	while (word->next)
	{
		k++;
		word = word->next;
	}
	word = tmp;
	return (k);
}

char		**ft_make_tabl(t_word *word)
{
	t_word	*tmp;
	int		k;
	char	**tabl;

	tmp = word;
	k = nb_chain(word);
	if (!(tabl = (char**)malloc(sizeof(char*) * (k + 1))))
		return (NULL);
	tabl[k] = 0;
	k = 0;
	while (word)
	{
		if (!(tabl[k] = ft_strdup(word->value)))
			return (NULL);
		word = word->next;
		k++;
	}
	word = tmp;
	return (tabl);
}
