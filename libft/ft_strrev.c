/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 14:56:36 by hben-yah          #+#    #+#             */
/*   Updated: 2019/06/04 14:58:53 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	char *b;
	char *e;
	char tmp;

	b = str;
	e = str + ft_strlen(str) - 1;
	while (b < e)
	{
		tmp = *b;
		*(b++) = *e;
		*(e--) = tmp;
	}
	return (str);
}
