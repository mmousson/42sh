/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 01:40:24 by mmousson          #+#    #+#             */
/*   Updated: 2019/02/12 10:30:57 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	size;
	void	*dup;

	if (s == NULL)
		return (NULL);
	size = ft_strlen(s) + 1;
	dup = malloc(size);
	if (dup == NULL)
		return (NULL);
	return ((char *)ft_memcpy(dup, s, size));
}
