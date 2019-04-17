/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 00:28:45 by mmousson          #+#    #+#             */
/*   Updated: 2019/03/11 19:40:24 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*memory;

	i = -1;
	memory = (unsigned char *)str;
	while (++i < n)
	{
		if (memory[i] == (unsigned char)c)
			return (memory + i);
	}
	return (NULL);
}
