/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   range.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 08:30:37 by hben-yah          #+#    #+#             */
/*   Updated: 2019/05/27 19:21:37 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void		walk_range(char **beg)
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
				return ;
			}
		}
		*str && ++str;
	}
	*beg = str;
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
				allow[(int)c++] = 1;
			s += 3;
		}
		else
			allow[(int)*s] = 1;
		++s;
	}
}
