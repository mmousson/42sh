/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdivide_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 06:48:13 by mmousson          #+#    #+#             */
/*   Updated: 2018/11/22 06:48:43 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdivide_two(char *str)
{
	int		nb;
	int		tmp;
	char	*bkp;

	tmp = 0;
	bkp = str;
	while (*str)
	{
		nb = *str - '0';
		nb *= 10;
		*str = ((nb / 2) / 10 + tmp) + '0';
		tmp = ((nb / 2) % 10);
		str++;
	}
	str = bkp;
	while (*str == '0')
		str++;
	str = ft_strdup(str);
	free(bkp);
	return (str);
}
