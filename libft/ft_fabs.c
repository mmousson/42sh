/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fabs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 16:02:57 by marvin            #+#    #+#             */
/*   Updated: 2019/03/06 02:24:05 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_fabs(double x)
{
	union u_fabs_matcher	matcher;

	matcher.double_corres = x;
	matcher.int_corres &= ~(1UL << 63);
	return (matcher.double_corres);
}
