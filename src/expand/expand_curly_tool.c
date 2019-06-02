/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_curly_tool.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 21:37:24 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/02 23:09:18 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expand.h"

char		*take_word_expand(const char *str, char ***arge)
{
	int		k;
	char	*word;
	int		pile;

	pile = 1;
	k = 0;
	while (str[k] && pile)
	{
		if (str[k] == '$' && str[k + 1] == '{')
			pile++;
		else if (str[k] == '}')
			pile--;
		k++;
	}
	word = ft_strsub(str, 0, k - 1);
	expand_param_word(&word, arge);
	return (word);
}
