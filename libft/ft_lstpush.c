/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 02:18:20 by mmousson          #+#    #+#             */
/*   Updated: 2018/11/15 05:32:33 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpush(t_list **alst, t_list *new)
{
	t_list *current;

	if (alst && new)
	{
		if (!*alst)
			*alst = new;
		else
		{
			current = *alst;
			while (current->next)
				current = current->next;
			current->next = new;
		}
	}
}
