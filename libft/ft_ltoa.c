/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 18:35:26 by hben-yah          #+#    #+#             */
/*   Updated: 2019/05/28 17:23:59 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_ltoa(long n)
{
	char			*s;
	size_t			len;
	unsigned long	nbr;
	unsigned long	m;

	len = 1;
	nbr = (unsigned long)n;
	if (n < 0)
	{
		nbr *= -1;
		++len;
	}
	m = nbr;
	while (m /= 10)
		++len;
	if (!(s = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	s[len] = 0;
	s[--len] = (char)((nbr % 10) + '0');
	while (nbr /= 10)
		s[--len] = (char)((nbr % 10) + '0');
	if (n < 0)
		*s = '-';
	return (s);
}
