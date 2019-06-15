/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_valid_to_atoi.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 00:23:28 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/13 09:11:00 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_valid_to_atoi(const char *str)
{
	size_t	i;

	i = 1;
	if (str == NULL)
		return (0);
	while (*str != '\0')
	{
		if (!(ft_isdigit(*str) || *str == 32 || (*str >= 9 && *str <= 13)
			|| *str == '+' || *str == '-'))
			return (0);
		if (i > 10)
			return (0);
		str++;
		i++;
	}
	return (1);
}
