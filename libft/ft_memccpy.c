/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 00:27:53 by mmousson          #+#    #+#             */
/*   Updated: 2018/11/08 06:27:59 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*src1;
	unsigned char	*dst1;

	i = 0;
	src1 = (unsigned char *)src;
	dst1 = (unsigned char *)dest;
	while (n--)
	{
		dst1[i] = src1[i];
		if (src1[i] == (unsigned char)c)
			return (dest + i + 1);
		i++;
	}
	return (NULL);
}
