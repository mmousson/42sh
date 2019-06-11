/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_valid_to_atoi.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 00:23:28 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/11 12:52:47 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_valid_to_atoi(const char *str)
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
