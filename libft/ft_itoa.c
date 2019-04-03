/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 06:45:12 by mmousson          #+#    #+#             */
/*   Updated: 2018/11/22 06:49:51 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_power(int base)
{
	size_t res;

	res = 1;
	while (base)
	{
		res *= 10;
		base--;
	}
	return (res);
}

static int		ft_mag(int nb)
{
	int	res;

	res = (nb >= 0) ? 1 : 2;
	nb *= (nb < 0) ? -1 : 1;
	while (nb >= 10)
	{
		nb /= 10;
		res++;
	}
	return (res);
}

char			*ft_itoa(int n)
{
	int		i;
	int		j;
	char	*num;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	i = 0;
	j = ft_mag((n >= 0) ? n : -n);
	if (!(num = (char *)malloc(sizeof(char) * j + (n < 0 ? 2 : 1))))
		return (NULL);
	ft_bzero(num, j + (n < 0 ? 2 : 1));
	if (n < 0)
	{
		num[i] = '-';
		n *= -1;
		i++;
	}
	while (i < (num[0] == '-' ? ft_mag(n) + 1 : ft_mag(n)))
	{
		num[i] = n / ft_power(j - 1) % 10 + 48;
		j--;
		i++;
	}
	num[i] = '\0';
	return (num);
}
