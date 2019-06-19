/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_words_tables.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 14:40:30 by roliveir          #+#    #+#             */
/*   Updated: 2019/06/11 12:43:05 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_del_words_tables(char ***tab)
{
	char	**tmp;

	if (!tab || !*tab)
		return ;
	tmp = *tab;
	while (**tab)
	{
		ft_strdel(*tab);
		*tab += 1;
	}
	free(tmp);
	tmp = NULL;
}
