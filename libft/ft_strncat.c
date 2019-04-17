/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 01:52:07 by mmousson          #+#    #+#             */
/*   Updated: 2018/11/07 22:23:17 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, char *src, size_t n)
{
	char	*result;

	result = dest;
	while (*dest)
		dest++;
	while (n-- && *src)
		*dest++ = *src++;
	*dest = '\0';
	return (result);
}
