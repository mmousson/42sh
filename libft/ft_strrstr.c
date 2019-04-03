/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 06:35:36 by mmousson          #+#    #+#             */
/*   Updated: 2019/01/22 01:46:16 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	len;

	if (*needle == '\0')
		return ((char *)haystack);
	i = ft_strlen(haystack);
	len = ft_strlen(needle);
	while (42)
	{
		if (ft_strncmp(haystack + (--i), needle, len) == 0)
			return ((char *)(haystack + i));
		if (i == 0)
			break ;
	}
	return (NULL);
}
