/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_name.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 04:19:55 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/06 05:41:04 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"
#include <stdlib.h>

static t_lsther		*init_lsther(char *str)
{
	t_lsther		*new;

	if (!(new = (t_lsther*)malloc(sizeof(t_lsther))))
		return (NULL);
	new->name = str;
	new->next = NULL;
	return (new);
}

void				add_name(t_red *red, char *str)
{
	t_lsther		*tmp;
	t_lsther		*new;

	if (!red)
		return ;
	new = init_lsther(str);
	if (!red->lsther)
		red->lsther = new;
	else
	{
		tmp = red->lsther;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
