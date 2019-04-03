/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dmin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 21:42:36 by mmousson          #+#    #+#             */
/*   Updated: 2019/03/06 03:05:48 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>

double	ft_dmin(int count, ...)
{
	va_list	ap;
	double	tmp;
	double	min;

	va_start(ap, count);
	min = __DBL_MAX__;
	while (count-- > 0)
	{
		tmp = va_arg(ap, double);
		if (tmp < min)
			min = tmp;
	}
	va_end(ap);
	return (min);
}
