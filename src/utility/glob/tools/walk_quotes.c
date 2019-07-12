/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walk_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:24:38 by hben-yah          #+#    #+#             */
/*   Updated: 2019/07/12 13:28:57 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"
#include "libft.h"

static int	is_specialchar(char c)
{
	return (c == '"' || c == '$' || c == '\\' || c == '\n');
}

void		walk_quote(char **str)
{
	char	*ptr;
	char	quote_val;

	ptr = *str;
	quote_val = *ptr;
	++ptr;
	while (*ptr)
	{
		if (*ptr == '\\' && quote_val == '"')
			++ptr;
		else if (*ptr == quote_val)
			break ;
		if (*ptr)
			++ptr;
	}
	*str = ptr;
}

void		walk_quote_unquote(char **str)
{
	char	*ptr;
	char	quote_val;

	ptr = *str;
	quote_val = *ptr;
	++ptr;
	while (*ptr)
	{
		if (*ptr == '\\' && is_specialchar(*(ptr + 1)) && quote_val == '"')
			ft_strrmvfirst(ptr);
		else if (*ptr == quote_val)
			break ;
		if (*ptr)
			++ptr;
	}
	*str = ptr;
}
