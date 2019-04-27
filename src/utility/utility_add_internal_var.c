/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_add_internal_var.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 06:20:40 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/27 15:15:36 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "sh42.h"

/*
**	This function allocate a new 't_vars' (typedef declared in sh42.h) link
**	and fills its fields 'name' and 'value' with a copy of the provided
**	arguments
**
**	Arguments:
**	name -> The 'name' field of the internal variable to create
**	value -> The 'value' field of the internal variable to create
**
**	Return Value:
**	NULL -> An Malloc error occured" nothing has been allocated
**	Otherwise, a pointer to a 't_vars' Data-Structure holding informations
**		of the newly created variable
*/

static t_vars	*create_new_link(char *name, char *value)
{
	t_vars	*result;

	if ((result = (t_vars *)ft_memalloc(sizeof(t_vars))) == NULL)
	{
		ft_putendl_fd("Internal Malloc Error", STDERR_FILENO);
		return (NULL);
	}
	result->name = ft_strdup(name);
	result->value = ft_strdup(value);
	if (result->name == NULL || result->value == NULL)
	{
		ft_putendl_fd("Internal Malloc Error", STDERR_FILENO);
		ft_strdel(&result->name);
		ft_strdel(&result->value);
		ft_memdel((void **)&(result));
	}
	return (result);
}

/*
**	This function adds a new internal variable defintion to the current
**	shell's list
**	It first tries to find an already-existing definition with the same name
**	If it succeeds in doing so, it will simply replace the 'value' field of
**	that definition and stop there
**	If no such definiton exists, it will create a new link to add to
**	the shell's list
**
**	Arguments:
**	name -> The 'name' field of the internal variable to create / modify
**	value -> The 'value' field of the internal variable to create / modify
**
**	Return Value: NONE
*/

void			utility_add_internal_var(char *name, char *value)
{
	t_vars	*prev;
	t_vars	*current;

	prev = NULL;
	current = shell_var_list;
	while (current)
	{
		if (ft_strequ(name, current->name))
		{
			ft_strdel(&current->value);
			if ((current->value = ft_strdup(value)) == NULL)
				ft_putendl_fd("Internal Malloc Error", STDERR_FILENO);
			return ;
		}
		prev = current;
		current = current->next;
	}
	current = create_new_link(name, value);
	if (prev == NULL)
		shell_var_list = current;
	else
		prev->next = current;
}
