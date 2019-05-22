/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 12:47:07 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/22 13:48:12 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

int				hist_strstr(char *haystack, char *needle)
{
	size_t		len;
	int			i;

	if (!haystack)
		return (-1);
	len = ft_strlen(needle);
	i = 0;
	if (*needle == '\0')
		return (-1);
	while (haystack[i])
	{
		if (!ft_strncmp(&(haystack[i]), needle, len))
			return (i);
		i++;
	}
	return (-1);
}
