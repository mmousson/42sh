/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_put_posix_string.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 02:21:35 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/13 02:34:23 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	utility_put_posix_string(const char *str)
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
