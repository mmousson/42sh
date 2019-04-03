/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 00:27:43 by mmousson          #+#    #+#             */
/*   Updated: 2018/11/06 02:47:56 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	unsigned char *memory;

	if (!(memory = (unsigned char *)malloc(size)))
		return (NULL);
	ft_memset(memory, 0, size);
	return ((void *)memory);
}
