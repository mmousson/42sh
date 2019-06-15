/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_purge_hash_table.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 16:27:32 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/13 08:59:30 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh42.h"

/*
**	This function will loop through the entire hashtable and clear every link
**	of every list of every occupied cell of the table, as well as free the
**	allocated memory occupied by excess elements
**
**	Arguments: NONE
**
**	Return Value: NONE
*/

void	utility_purge_hash_table(void)
{
	int		i;
	int		not_base;
	t_hash	*current;
	t_hash	*next;

	i = -1;
	while (++i < HASH_MOD)
	{
		if (g_hash[i].full_path != NULL)
		{
			not_base = 0;
			current = &(g_hash[i]);
			while (current)
			{
				next = current->next;
				current->hits = 0;
				ft_strdel(&(current->utility_name));
				ft_strdel(&(current->full_path));
				if (not_base)
					ft_memdel((void **)&(current));
				current = next;
				not_base = 1;
			}
		}
	}
}
