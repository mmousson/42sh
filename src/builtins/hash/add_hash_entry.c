/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_hash_entry.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 22:24:24 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/16 00:38:08 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh42.h"

/*
**	This function adds the 'full_path' string at the 'string_hash' index
**	in the shell's hashtable
**	If the index designated by 'string_hash' is already occupied
**	(as in the fields are NON-NULL), then we have a collision
**	Collision is resolved that way:
**	Each element of the hashtable is a linked list. To store an element in the
**	hashtable we insert it in a specific linked list (at index 'string_hash')
**	If multiple elements result in the same hash, insert all of them in the
**	same list
**
**	Arguments:
**	string_hash -> The hash computed by the function 'hash_string' which will
**		be used as the the elements index
**	full_path -> The element to store in the hashtable
**
**	Return Value: NONE
*/

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
