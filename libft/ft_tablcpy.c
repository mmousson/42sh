/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tablcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 15:06:21 by hben-yah          #+#    #+#             */
/*   Updated: 2019/05/27 20:24:09 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_tablcpy(void **dst, void **src, size_t size)
{
	size_t	len;

	len = 0;
	if (size > 0)
	{
		while (src[len] && len < size - 1)
		{
			dst[len] = src[len];
			++len;
		}
		dst[len] = 0;
	}
	while (src[len])
		++len;
	return (len);
}
