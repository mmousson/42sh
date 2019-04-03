/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strremove_at.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 04:02:20 by mmousson          #+#    #+#             */
/*   Updated: 2018/12/31 04:13:55 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strremove_at(char *str, size_t index)
{
	if (str == NULL || ft_strlen(str) < index)
		return ;
	while (*str != '\0' && index-- > 0)
		str++;
	while (*str != '\0')
	{
		*str = *(str + 1);
		str++;
	}
}
