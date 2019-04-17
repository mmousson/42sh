/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 02:00:15 by mmousson          #+#    #+#             */
/*   Updated: 2018/11/08 02:56:36 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t len;

	len = ft_strlen(str) - 1;
	if (!c)
		return ((char *)(str + len + 1));
	while (str[len] && str[len] != (char)c && len)
		len--;
	if (str[len] == (char)c)
		return ((char *)(str + len));
	return (NULL);
}
