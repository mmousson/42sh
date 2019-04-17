/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 05:27:50 by mmousson          #+#    #+#             */
/*   Updated: 2018/11/08 04:31:50 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_is_space(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

char		*ft_strtrim(char const *s)
{
	size_t i;
	size_t j;

	i = 0;
	if (!s)
		return (NULL);
	if (*s == '\0')
		return (ft_strdup(""));
	while (ft_is_space(s[i]))
		i++;
	if (s[i] == '\0')
		return (ft_strdup(""));
	j = ft_strlen(s);
	while (ft_is_space(s[j - 1]) && j > i)
		j--;
	return (ft_strsub(s, i, (j - i)));
}
