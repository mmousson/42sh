/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 03:26:50 by mmousson          #+#    #+#             */
/*   Updated: 2018/11/08 06:50:03 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned	i;
	unsigned	len;
	char		*res;

	i = -1;
	if (s && f && (len = ft_strlen(s)))
	{
		if (!(res = (char *)malloc(len + 1)))
			return (NULL);
		else
			while (++i < len)
				res[i] = f(i, s[i]);
	}
	else
		return (NULL);
	res[i] = '\0';
	return (res);
}
