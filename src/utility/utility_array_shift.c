/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_array_shift.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 16:35:55 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/10 19:26:59 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	utility_array_shift(char **to_shift)
{
	int	i;

	if (to_shift == NULL)
		return ;
	i = 0;
	ft_strdel(&(to_shift[0]));
	while (42)
	{
		to_shift[i] = to_shift[i + 1];
		if (to_shift[i] == NULL)
			break ;
		else
			i++;
	}
}
