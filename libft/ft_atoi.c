/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 00:23:28 by mmousson          #+#    #+#             */
/*   Updated: 2019/02/19 13:59:47 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *s)
{
	int				neg;
	long long int	res;

	if (s == NULL)
		return (0);
	neg = 1;
	res = 0;
	while (*s == 32 || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			neg = -1;
		s++;
	}
	while (*s >= '0' && *s <= '9')
	{
		res = (res * 10LL) + (long long)(*s - '0');
		s++;
	}
	return ((int)(res * neg));
}
