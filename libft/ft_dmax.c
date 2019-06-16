/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dmax.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 21:37:02 by mmousson          #+#    #+#             */
/*   Updated: 2019/03/06 03:05:52 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>

double	ft_dmax(int count, ...)
{
	va_list	ap;
	double	tmp;
	double	max;

	va_start(ap, count);
	max = __DBL_MIN__;
	while (count-- > 0)
	{
		tmp = va_arg(ap, double);
		if (tmp > max)
			max = tmp;
	}
	va_end(ap);
	return (max);
}
