/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_add_hash_entry.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 22:24:24 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/17 11:25:58 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh42.h"

int		hash_already_exists(int index, char *name)
{
	t_hash	*current;

	current = &(g_hash[index]);
	while (current)
	{
		if (ft_strequ(current->utility_name, name))
			return (1);
		current = current->next;
	}
	return (0);
}

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

void	hash_add_entry(int string_hash, char *util_name, char *full_path,
																	int value)
{
	t_hash	*target;
	t_hash	*new_entry;

	if (hash_already_exists(string_hash, util_name))
		return ;
	if (g_hash[string_hash].full_path == NULL)
	{
		g_hash[string_hash].hits = value;
		g_hash[string_hash].full_path = ft_strdup(full_path);
		g_hash[string_hash].utility_name = ft_strdup(util_name);
	}
	else
	{
		if ((new_entry = (t_hash *)ft_memalloc(sizeof(t_hash))) == NULL)
			return ;
		new_entry->hits = value;
		new_entry->full_path = ft_strdup(full_path);
		new_entry->utility_name = ft_strdup(util_name);
		new_entry->next = NULL;
		target = &(g_hash[string_hash]);
		while (target->next)
			target = target->next;
		target->next = new_entry;
	}
}
