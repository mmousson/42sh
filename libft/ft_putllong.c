/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putllong.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 01:06:40 by mmousson          #+#    #+#             */
/*   Updated: 2018/11/06 01:06:41 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putllong(long long ll)
{
	if (ll < 0)
	{
		ft_putchar('-');
		ft_putllong(-ll);
	}
	else
	{
		if (ll >= 10)
			ft_putllong(ll / 10);
		ft_putchar('0' + ll % 10);
	}
}
