/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 00:30:03 by mmousson          #+#    #+#             */
/*   Updated: 2018/11/08 02:44:32 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *str1, const void *str2, size_t n)
{
	size_t			i;
	unsigned char	*src;
	unsigned char	*dest;

	i = 0;
	src = (unsigned char *)str2;
	dest = (unsigned char *)str1;
	while (n--)
	{
		dest[i] = src[i];
		i++;
	}
	return (str1);
}
