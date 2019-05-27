/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walk_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:24:38 by hben-yah          #+#    #+#             */
/*   Updated: 2019/05/27 19:20:28 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"
#include "libft.h"

void		walk_quote(char **str)
{
	char	*ptr;
	char	quote_val;

	ptr = *str;
	quote_val = *ptr;
	ptr++;
	while (*ptr)
	{
		if (*ptr == '\\' && is_quote(*(ptr + 1)) && quote_val == '"')
			ft_strrmvfirst(ptr);
		else if (*ptr == quote_val)
			break ;
		++ptr;
	}
	*str = ptr;
}
