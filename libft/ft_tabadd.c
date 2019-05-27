/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 11:11:16 by hben-yah          #+#    #+#             */
/*   Updated: 2019/05/27 19:27:00 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_tabadd(void ***tab, void *new)
{
	size_t	len;

	if (!tab)
		return (0);
	len = *tab ? ft_tablen(*tab) : 0;
	if (!(*tab = ft_tabrealloc(*tab, len + 1)))
	{
		ft_tabdel(tab);
		return (0);
	}
	(*tab)[len] = new;
	(*tab)[len + 1] = NULL;
	return (1);
}

int		ft_strtabadd(char ***tab, char *new)
{
	return (ft_tabadd((void ***)tab, (void *)new));
}
