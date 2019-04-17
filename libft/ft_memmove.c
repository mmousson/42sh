/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 00:31:26 by mmousson          #+#    #+#             */
/*   Updated: 2019/03/11 19:40:47 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *str1, const void *str2, size_t n)
{
	char *src;
	char *dest;

	if (str1 == str2)
		return (str1);
	src = (char *)str2;
	dest = (char *)str1;
	if (str2 < str1)
	{
		while ((int)n--)
			dest[n] = src[n];
	}
	else
		ft_memcpy(str1, str2, n);
	return (str1);
}
