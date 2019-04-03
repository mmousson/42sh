/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 01:44:47 by mmousson          #+#    #+#             */
/*   Updated: 2018/11/09 05:52:45 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	char	*tmp;
	size_t	dest_len;
	size_t	src_len;

	tmp = dest;
	src_len = ft_strlen(src);
	if (!size)
		return (ft_strlen(src));
	while (*tmp && (--size > 0))
		tmp++;
	dest_len = ((size ? tmp : ++tmp) - dest);
	if (size)
	{
		while (*src && size--)
			*(tmp++) = *(src++);
		*(tmp - ((*src || !size) ? 1 : 0)) = '\0';
	}
	return (dest_len + src_len);
}
