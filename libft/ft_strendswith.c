/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strendswith.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 18:04:10 by mmousson          #+#    #+#             */
/*   Updated: 2019/01/22 01:54:19 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strendswith(char *str, const char *end)
{
	size_t	end_len;
	size_t	str_len;

	if (str == NULL || end == NULL || *str == '\0')
		return (0);
	end_len = ft_strlen(end);
	str_len = ft_strlen(str);
	str += str_len - end_len;
	while (*str != '\0' && *end != '\0')
	{
		if (*str != *end)
			return (0);
		str++;
		end++;
	}
	if (*str == '\0' && *end == '\0')
		return (1);
	else
		return (0);
}
