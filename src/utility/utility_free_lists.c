/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_free_lists.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 06:12:09 by mmousson          #+#    #+#             */
/*   Updated: 2019/05/24 21:07:45 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh42.h"

/*
**	Function to free the shell's internal variables definition
**
**	Arguments: NONE
**
**	Return Value: NONE
*/

void	utility_free_shell_vars_list(void)
{
	t_vars	*ptr;
	t_vars	*next;

	ptr = g_shell_var_list;
	while (ptr)
	{
		next = ptr->next;
		ft_strdel(&(ptr->name));
		ft_strdel(&(ptr->value));
		ft_memdel((void **)&(ptr));
		ptr = next;
	}
}

/*
**	Nothing to say here
**
**	Arguments: NONE
**
**	Return Value: NONE
*/

void	utility_free_alias_list(void)
{
	t_alias	*next;

	while (g_alias_list)
	{
		ft_strdel(&(g_alias_list->token));
		ft_strdel(&(g_alias_list->replacement));
		next = g_alias_list->next;
		ft_memdel((void **)&(g_alias_list));
		g_alias_list = next;
	}
}
