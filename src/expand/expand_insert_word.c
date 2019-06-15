/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_insert_word.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 20:56:29 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/15 16:36:32 by oboutrol         ###   ########.fr       */
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
			ft_strdel(str);
			if (!(*str = ft_strjoin(*first, *end)))
				return (1);
			ft_strdel(first);
			ft_strdel(end);
		}
		else
		{
			ft_strdel(str);
			*str = *first;
			*first = NULL;
		}
	}
	else
	{
		ft_strdel(str);
		*str = *end;
		*end = NULL;
	}
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
