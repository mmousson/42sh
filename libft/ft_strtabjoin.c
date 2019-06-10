/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtabjoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 16:09:47 by hben-yah          #+#    #+#             */
/*   Updated: 2019/06/10 16:10:03 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_strtabjoin(char **tab1, char **tab2)
{
	char	**res;
	size_t	len1;

	len1 = tab1 ? ft_strtablen(tab1) : 0;
	if ((res = ft_strtaballoc(len1 + (tab2 ? ft_strtablen(tab2) : 0))))
	{
		if (tab1)
			ft_strtabcpy(res, tab1);
		if (tab2)
			ft_strtabcpy(res + len1, tab2);
	}
	return (res);
}

char		**ft_strtabjoin3(char **tab1, char **tab2, char **tab3)
{
	char	**res;
	size_t	len1;
	size_t	len2;

	len1 = tab1 ? ft_strtablen(tab1) : 0;
	len2 = tab2 ? ft_strtablen(tab2) : 0;
	if ((res = ft_strtaballoc(len1 + len2 + (tab3 ? ft_strtablen(tab3) : 0))))
	{
		if (tab1)
			ft_strtabcpy(res, tab1);
		if (tab2)
			ft_strtabcpy(res + len1, tab2);
		if (tab3)
			ft_strtabcpy(res + len1 + len2, tab3);
	}
	return (res);
}

char		**ft_strtabjoin4(char **tab1, char **tab2, char **tab3, char **tab4)
{
	char	**res;
	size_t	len1;
	size_t	len2;
	size_t	len3;

	len1 = tab1 ? ft_strtablen(tab1) : 0;
	len2 = tab2 ? ft_strtablen(tab2) : 0;
	len3 = tab3 ? ft_strtablen(tab3) : 0;
	if ((res = ft_strtaballoc(len1 + len2 + len3 + (tab4 ? ft_strtablen(tab4) : 0))))
	{
		if (tab1)
			ft_strtabcpy(res, tab1);
		if (tab2)
			ft_strtabcpy(res + len1, tab2);
		if (tab3)
			ft_strtabcpy(res + len1 + len2, tab3);
		if (tab4)
			ft_strtabcpy(res + len1 + len2 + len3, tab4);
	}
	return (res);
}