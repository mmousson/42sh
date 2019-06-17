/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_put_posix_string.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 02:21:35 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/17 10:26:09 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	utility_str_must_be_quoted(const char *str)
{
	int	ret;

	ret = 0;
	while (*str)
	{
		if (*str == '*' || *str == '$' || *str == ';' )
			ret |= 1;
		else if (*str == '=')
			ret |= 2;
		str++;
	}
	return (ret);
}

void		utility_put_set_posix_str(const char *str)
{
	int	quote;

	if (str == NULL || *str == '\0')
		return ;
	quote = utility_str_must_be_quoted(str);
	if (!(quote & 2) && (quote & 1))
		ft_putchar('\'');
	while (*str != '\0')
	{
		if (*str == '\'' || *str == '\"')
			ft_putchar('\\');
		ft_putchar(*str);
		if (*str == '=' && (quote & 1) && !(quote & 4))
		{
			ft_putchar('\'');
			quote |= 4;
		}
		str++;
	}
	if (quote & 1)
		ft_putchar('\'');
}

void		utility_put_posix_string(const char *str)
{
	if (str == NULL)
		return ;
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
			ft_putchar('\\');
		ft_putchar(*str);
		if (*str == '=')
			ft_putchar('\"');
		str++;
	}
	ft_putchar('\"');
}
