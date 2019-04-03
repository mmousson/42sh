/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 04:22:29 by mmousson          #+#    #+#             */
/*   Updated: 2019/02/12 04:00:00 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char *res;

	if (!s || !(res = (char *)ft_memalloc(len + 1)))
		return (NULL);
	ft_strncpy(res, s + start, len);
	res[len] = '\0';
	return (res);
}
