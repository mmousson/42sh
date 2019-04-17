/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 15:18:25 by roliveir          #+#    #+#             */
/*   Updated: 2019/01/30 07:51:16 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

char		*ft_strnew(size_t size)
{
	char	*mem;
	size_t	i;

	i = 0;
	if (!(mem = (char*)malloc(size + 1)))
		return (NULL);
	ft_bzero(mem, size);
	mem[size] = '\0';
	return (mem);
}
