/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 19:24:44 by hben-yah          #+#    #+#             */
/*   Updated: 2019/05/29 14:10:29 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_tabdel(void ***tab)
{
	void **t;

	if (tab && *tab)
	{
		t = *tab;
		while (*t)
			ft_memdel(t++);
		free(*tab);
		*tab = NULL;
	}
}

void	ft_strtabdel(char ***tab)
{
	ft_tabdel((void ***)tab);
}

void	ft_strtabdel2(char ***tab1, char ***tab2)
{
	ft_tabdel((void ***)tab1);
	ft_tabdel((void ***)tab2);
}
