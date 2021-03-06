/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:20:18 by hben-yah          #+#    #+#             */
/*   Updated: 2019/07/04 14:36:43 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"
#include "libft.h"

size_t		expansion_unquote(char *str)
{
	char	*endquote;
	char	*beg;

	if ((beg = str))
		while (*str)
		{
			if (*str == '\\')
				ft_strrmvfirst(str);
			else if (is_quote(*str))
			{
				endquote = str;
				walk_quote_unquote(&endquote);
				if (*endquote == *str)
				{
					ft_strrmvfirst(endquote);
					ft_strrmvfirst(str);
					if (endquote - str > 2)
						str = endquote - 2;
				}
			}
			if (*str)
				++str;
		}
	return ((size_t)(str - beg));
}
