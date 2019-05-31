/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_delete_var.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 07:46:01 by mmousson          #+#    #+#             */
/*   Updated: 2019/05/31 18:12:43 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh42.h"

/*
**	This function deletes an internal variable definition from the
**	'g_shell_var_list' global variable and, if it doesn;t exist in the global,
**	from the shell's current environment array
**
**	name -> The name of the variable we want to delete
**	env -> The shell's current environment array
**
**	Return Value: NONE
*/

void	utility_delete_var(char *name, char ***env)
{
	char	*ret;
	t_vars	*holder;
	t_vars	*holder_next;

	if ((ret = utility_internal_var_exists(name, &holder)) != NULL)
	{
		if (holder == g_shell_var_list)
			g_shell_var_list = g_shell_var_list->next;
		holder_next = holder->next;
		if (holder_next != NULL)
			holder_next->prev = holder->prev;
		if (holder->prev != NULL)
			holder->prev->next = holder_next;
		ft_strdel(&holder->name);
		ft_strdel(&holder->value);
		ft_memdel((void **)&(holder));
	}
	else
		utility_rm_entry_from_environ(env, name);
}
