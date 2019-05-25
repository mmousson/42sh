/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_param.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 14:27:00 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/25 10:42:11 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"
#include "expand.h"
#include "libft.h"
#include <stdlib.h>

int			is_char_exp(char c)
{
	int			k;

	k = 0;
	if (!c)
		return (0);
	if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_'
			|| (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

char		*expand_param(const char *str, char ***arge, int *end)
{
	char	*value;
	char	*word;
	int		k;

	if (!str)
		return (NULL);
	k = 0;
	while (is_char_exp(str[k]))
		k++;
	word = ft_strsub(str, 1, k);
	value = ft_getenv(*arge, word);
	ft_strdel(&word);
	*end = k;
	return (value);
}
