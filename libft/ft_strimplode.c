/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strimplode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 18:52:44 by hben-yah          #+#    #+#             */
/*   Updated: 2019/05/27 19:16:44 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strimplode(char **tab, char delim)
{
	char	*ret;
	size_t	len;
	size_t	i;

	if (!tab || !*tab)
		return (NULL);
	i = 0;
	len = ft_tabstrlen(tab, &i) + i - 1;
	if (!(ret = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (*tab)
	{
		if (i > 0)
			ret[i++] = delim;
		i += ft_strlcpy(ret + i, *(tab++), len + 1);
	}
	return (ret);
}

char		*ft_strimplodef(char **tab, char delim)
{
	char	*ret;

	if (!(ret = ft_strimplode(tab, delim)))
		return (NULL);
	ft_strtabdel(&tab);
	return (ret);
}
