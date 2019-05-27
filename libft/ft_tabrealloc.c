/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabrealloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 11:19:24 by hben-yah          #+#    #+#             */
/*   Updated: 2019/05/27 20:21:35 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	**ft_tabrealloc(void **tab, size_t len)
{
	void **ret;

	ret = NULL;
	if (len > 0)
	{
		if (!(ret = ft_taballoc(len)))
			return (NULL);
		if (tab)
		{
			ft_tablcpy(ret, tab, len + 1);
			ret[len] = NULL;
			free(tab);
		}
		else
			*ret = NULL;
	}
	else if (tab)
		ft_tabdel(&tab);
	return (ret);
}
