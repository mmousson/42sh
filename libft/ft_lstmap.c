/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 18:55:13 by mmousson          #+#    #+#             */
/*   Updated: 2018/11/08 06:58:26 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new;
	t_list *bkp;

	if (lst && f)
	{
		new = f(lst);
		lst = lst->next;
	}
	else
		return (NULL);
	bkp = new;
	while (lst)
	{
		new->next = f(lst);
		lst = lst->next;
		new = new->next;
	}
	return (bkp);
}
