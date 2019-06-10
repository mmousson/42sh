/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_insert_word.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 20:56:29 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/09 21:16:33 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	insert_paste(char **str, char **end, char **first)
{
	if (*first)
	{
		if (*end)
		{
			if (!(*str = ft_strjoin(*first, *end)))
				return (1);
			ft_strdel(first);
			ft_strdel(end);
		}
		else
			*str = *first;
	}
	else
		*str = *end;
	return (0);
}

int			insert_word(char **str, char *expand, int start, int len)
{
	char	*first;
	char	*end;
	char	*tmp;

	if (start < 0 || len < 0 || !str || !(*str))
		return (0);
	first = ft_strsub(*str, 0, start);
	end = ft_strsub(*str, start + len + 1, ft_strlen(*str) - start - len);
	free(*str);
	if (expand)
	{
		tmp = first;
		if (!(first = ft_strjoin(first, expand)))
			return (1);
		ft_strdel(&tmp);
	}
	if (insert_paste(str, &end, &first))
		return (1);
	return (0);
}
