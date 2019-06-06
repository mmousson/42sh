/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   range.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 08:30:37 by hben-yah          #+#    #+#             */
/*   Updated: 2019/06/06 14:22:30 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // a virer

int		walk_range(char **beg)
{
	char	*ptr;
	char	*str;

	str = *beg;
	while (*str)
	{
		if (*str == ']')
		{
			ptr = str + 1;
			while (*ptr && *ptr != ']' && *ptr != '[')
				++ptr;
			if (!*ptr || *ptr == '[')
			{
				*beg = str;
				return (0);
			}
		}
		if (*str)
			++str;
	}
	return (1);
}

void		parse_range(char *allow, char *s)
{
	char c;

	while (*s)
	{
		if (*(s + 1) == '-' && *(s + 2) && *(s + 3))
		{
			c = *s;
			while (c <= *(s + 2))
				allow[(unsigned char)c++] = 1;
			s += 3;
		}
		else
			allow[(unsigned char)*s] = 1;
		++s;
	}
}
