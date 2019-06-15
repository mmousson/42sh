/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 01:46:00 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/13 02:41:53 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	const char *tmp;

	if (str == NULL)
		return (0);
	tmp = str;
	while (*(tmp) != 0)
		tmp++;
	return (tmp - str);
}
