/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_add_internal_var.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 08:24:16 by mmousson          #+#    #+#             */
/*   Updated: 2019/05/14 08:25:15 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh42.h"

/*
**	This function is called by the 'utility_set_var' wrapper function
**	It creates a new link and fills it with the value given by the arguments
**	'name' and 'value' and then prepends the link to the current linked list,
**	updating its head pointer
**	In case of memory allocation error, nothing is modified
**
**	Arguments:
**	name -> The name of the variable to create in the linked list
**	value -> The value of the wanted variable definition
**
**	Return Value: NONE
*/

void	utility_add_internal_var(char *name, char *value)
{
	t_vars	*internal;

	if ((internal = (t_vars *)ft_memalloc(sizeof(t_vars))) == NULL)
		ft_putendl_fd("42sh: Internal Malloc Error", STDERR_FILENO);
	else
	{
		internal->name = NULL;
		internal->value = NULL;
		if ((internal->name = ft_strdup(name)) == NULL
			|| (internal->value = ft_strdup(value)) == NULL)
		{
			ft_putendl_fd("42sh: Internal Malloc Error", STDERR_FILENO);
			ft_strdel(&internal->name);
			ft_strdel(&internal->value);
			ft_memdel((void **)&(internal));
		}
		else
		{
			internal->prev = NULL;
			internal->next = g_shell_var_list;
			if (g_shell_var_list != NULL)
				g_shell_var_list->prev = internal;
			g_shell_var_list = internal;
		}
	}
}
