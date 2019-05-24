/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_insert_word.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 20:56:29 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/24 22:11:51 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		insert_word(char **str, char *expand, int start, int len)
{
	char *first;
	char *end;

	if (start < 0 || len < 0 || !str || !(*str) || !(expand))
		return (0);
	first = ft_strsub(*str, 0, start);
	end = ft_strsub(*str, start + len + 1, ft_strlen(*str) - start - len);
	free(*str);
	if (!(*str = ft_strjoin(first, expand)))
		return (1);
	if (!(*str = ft_strjoin(*str, end)))
		return (1);
	return (0);
}
