/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 01:51:39 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/25 06:44:12 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unset.h"

/*
**	This function will delete a variable 'name'
**	from the shell's internal variables list
**
**	Arguments:
**	name -> The variable's name to look for
**
**	Return Value: NONE
*/

static void	search_in_shell_internal_vars(char *name)
{
	t_vars	*current;
	t_vars	*prev;

	prev = NULL;
	current = shell_var_list;
	while (current)
	{
		if (ft_strequ(name, current->name))
		{
			if (prev == NULL)
				shell_var_list = current->next;
			else
				prev->next = current->next;
			ft_strdel(&current->name);
			ft_strdel(&current->value);
			ft_memdel((void **)&(current));
		}
		prev = current;
		current = current->next;
	}
}

/*
**	This functions will delete a variable 'name'
**	from the shell's environment
**
**	Arguments:
**	name -> The variable's name to look for
**	env -> The shell's environment array
**
**	Return Value: NONE
*/

static void	search_in_environment(char *name, char ***env)
{
	int	i;

	i = -1;
	while ((*env)[++i] != NULL)
		ft_rm_entry_from_environ(env, name);
}

/*
**	============================= BUITLIN COMMAND =============================
**	Main function for the 'unset' utility
**	No accepted options
**	The normal behaviour of this utility is to remove all variables whose name
**	are listed in the utility arguments
**	from the shell's internal variables list AND the environment
**
**	Return Value: ALWAYS 0
*/
int	unset(int argc, char **argv, char ***env)
{
	int		i;

	i = 0;
	while (++i < argc)
	{
		search_in_environment(argv[i], env);
		search_in_shell_internal_vars(argv[i]);
	}
	return (0);
}
