/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_order_of_magnitude.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 22:31:35 by mmousson          #+#    #+#             */
/*   Updated: 2019/05/06 19:20:03 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_order_of_magnitude(int nb)
{
	int	res;

	if (nb <= 0)
		res = 1;
	else
		res = 0;
	if (nb < 0)
		nb = nb * (-1);
	while (nb)
	{
		res++;
		nb /= 10;
	}
	return (res);
}
