/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 18:17:41 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/15 17:53:13 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*to_del;
	void	*tmp;

	if (alst && *alst)
		to_del = *alst;
	else
		return ;
	if (to_del->content)
	{
		tmp = to_del->content;
		del(to_del->content, to_del->content_size);
		free(tmp);
	}
	ft_memdel((void **)alst);
}
