/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_nb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 18:02:02 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/11 19:49:37 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int					ft_count_n(int nbr)
{
	unsigned int	val;
	int				count;

	count = 0;
	if (nbr < 0)
		val = -nbr;
	else
		val = nbr;
	if (!nbr || nbr < 0)
		count++;
	while (val)
	{
		val = val / 10;
		count++;
	}
	return (count);
}
