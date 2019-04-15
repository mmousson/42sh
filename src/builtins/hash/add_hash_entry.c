/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_hash_entry.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 22:24:24 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/15 23:14:54 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh42.h"

void		add_hash_entry(int string_hash, char *full_path)
{
	t_hash	*target;
	t_hash	*new_entry;

	if (g_hash[string_hash].full_path == NULL)
	{
		g_hash[string_hash].hits = 0;
		g_hash[string_hash].full_path = ft_strdup(full_path);
	}
	else
	{
		if ((new_entry = (t_hash *)ft_memalloc(sizeof(t_hash))) == NULL)
			return ;
		new_entry->hits = 0;
		new_entry->full_path = ft_strdup(full_path);
		new_entry->next = NULL;
		target = &(g_hash[string_hash]);
		while (target->next)
			target = target->next;
		target->next = new_entry;
	}
}
