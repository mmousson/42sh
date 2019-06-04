/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_valid_to_atoi.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 13:02:00 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/04 13:02:00 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_valid_to_atoi(const char *str)
{
	if (str == NULL)
		return (0);
	while (*str != '\0')
	{
		if (!(ft_isdigit(*str) || *str == 32 || (*str >= 9 || *str <= 13)))
			return (0);
		str++;
	}
	return (1);
}
