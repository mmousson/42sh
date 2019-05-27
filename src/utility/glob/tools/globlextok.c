/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globlextok.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 13:14:48 by hben-yah          #+#    #+#             */
/*   Updated: 2019/05/27 19:20:55 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"
#include "libft.h"

t_globtok		*globtok_last(t_globtok *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

unsigned int	globlexlen(t_globlex *container)
{
	unsigned int	len;
	t_globtok		*ptr;

	len = 0;
	if (container)
	{
		ptr = container->first;
		while (ptr)
		{
			++len;
			ptr = ptr->next;
		}
	}
	return (len);
}

t_globlex		*globlexnew(void *content)
{
	t_globlex *new;

	if (!(new = (t_globlex*)ft_memalloc(sizeof(t_globlex))))
		return (0);
	if (content)
	{
		new->first = content;
		new->last = globtok_last(content);
		new->len = globlexlen(new);
	}
	return (new);
}

t_globtok		*globtoknew(void *data)
{
	t_globtok *new;

	if (!(new = (t_globtok*)ft_memalloc(sizeof(*new))))
		return (0);
	new->data = data;
	return (new);
}

t_globtok		*globlex_pushback(t_globlex *container, void *data)
{
	t_globtok	*new;
	t_globtok	*ptr;

	if (!data || !(new = globtoknew(data)))
		return (0);
	if (!(ptr = container->first))
		container->first = new;
	else
	{
		ptr = container->last;
		new->prev = ptr;
		ptr->next = new;
	}
	container->last = new;
	container->len++;
	return (new);
}
