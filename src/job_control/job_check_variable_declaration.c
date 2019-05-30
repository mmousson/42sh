/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_check_variable_declaration.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 16:52:29 by mmousson          #+#    #+#             */
/*   Updated: 2019/05/30 16:52:29 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh42.h"
#include "job_control_42.h"

/*
**
*/

static void	update_variables(char *name, char *value, t_process *proc)
{
	utility_add_internal_var(name, value);
	ft_strdel(&name);
	ft_strdel(&value);
	ft_strdel(&(proc->name));
	proc->name = ft_strdup(proc->argv[1]);
	utility_array_shift(proc->argv);
}

/*
**
*/

static int	update_dropped_process_informations(t_process *proc)
{
	proc->valid_to_wait_for = false;
	proc->status = 0;
	proc->completed = true;
	return (DROP_PROCESS);
}

/*
**	This function loops through a process's arguments and until it meets an
**	an argument that is not formatted like a variable declaration
**	At first, all declarations are stored in a separate place (a linked list)
**	and once the loop stops, it is decided whether the declarations should
**	affect the Internal Variables table, or the Temporary Variables table
**	If all arguments have been consumed -> Internal Vars
**	If there are arguments left -> Temporary Vars
**
**	Arguments:
**	proc -> A pointer to the Data-Strucure holding informations about
**		the process having possible varaible declaration
**
**	Return Value:
**	DROP (0) -> All arguments have been consumeed by variable declarations
**		There is nothing more to be done
**	CONTINUE (1) -> There are still arguments left after variable declarations
**		JC engine must therefore try to start the process
*/

int			job_check_variable_declaration(t_process *proc)
{
	char	*catch;
	char	*name;
	char	*value;
	size_t	name_len;
	size_t	val_len;

	while ((catch = ft_strchr(proc->argv[0], '=')) != NULL)
	{
		if (!(name = ft_strsub(proc->argv[0], 0, catch - proc->argv[0])))
		{
			ft_putendl_fd("42sh: Internal Malloc Error", STDERR_FILENO);
			return (DROP_PROCESS);
		}
		name_len = ft_strlen(name) + 1;
		val_len = ft_strlen(proc->argv[0]) - name_len;
		if ((value = ft_strsub(proc->argv[0], name_len, val_len)) == NULL)
		{
			ft_putendl_fd("42sh: Internal Malloc Error", STDERR_FILENO);
			return (DROP_PROCESS);
		}
		update_variables(name, value, proc);
		if (proc->argv[0] == NULL)
			return (update_dropped_process_informations(proc));
	}
	return (CONTINUE_PROCESS);
}
