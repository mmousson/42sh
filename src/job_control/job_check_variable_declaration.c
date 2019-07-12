/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_check_variable_declaration.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 16:52:29 by mmousson          #+#    #+#             */
/*   Updated: 2019/07/12 13:27:08 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh42.h"
#include "job_control_42.h"

static int		list_manager(int flag, t_vars *element, char ***env)
{
	static t_vars	*local_ref = NULL;
	t_vars			*next;

	if (flag == VAR_ADD)
	{
		if (element == NULL)
			return (-1);
		element->next = local_ref;
		local_ref = element;
	}
	else
		while (local_ref != NULL)
		{
			next = local_ref->next;
			if (flag == VAR_PUSH_INTERNAL)
				utility_set_var(local_ref->name, local_ref->value, env, 0);
			else if (flag == VAR_PUSH_TMP)
				utility_add_tmp_var(local_ref->name, local_ref->value);
			ft_strdel(&local_ref->name);
			ft_strdel(&local_ref->value);
			ft_memdel((void **)&(local_ref));
			local_ref = next;
		}
	return (1);
}

static t_vars	*new_var(char *name, char *value, t_process *proc)
{
	int		i;
	t_vars	*result;

	if (name == NULL || value == NULL || *name == '\0')
		return (NULL);
	i = -1;
	while (name[++i] != '\0')
		if (!(ft_isalpha(name[i]) || name[i] == '_'))
			return (NULL);
	ft_strdel(&(proc->name));
	proc->name = ft_strdup(proc->argv[1]);
	utility_array_shift(proc->argv);
	if ((result = ft_memalloc(sizeof(t_vars))) == NULL)
	{
		ft_putendl_fd("42sh: Internal Malloc Error", STDERR_FILENO);
		return (NULL);
	}
	result->name = name;
	result->value = value;
	return (result);
}

static int		update_dropped_process_informations(t_process *proc,
	char ***env)
{
	list_manager(VAR_PUSH_INTERNAL, NULL, env);
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
**	env -> The shell's current environment
**
**	Return Value:
**	DROP (0) -> All arguments have been consumeed by variable declarations
**		There is nothing more to be done
**	CONTINUE (1) -> There are still arguments left after variable declarations
**		JC engine must therefore try to start the process
*/

int				job_check_variable_declaration(t_process *proc, char ***env)
{
	char	*catch;
	char	*name;
	char	*value;
	size_t	val_len;

	if (proc->compound)
		return (CONTINUE_PROCESS);
	while ((catch = ft_strchr(proc->argv[0], '=')) != NULL)
	{
		if (!(name = ft_strsub(proc->argv[0], 0, catch - proc->argv[0])))
		{
			ft_putendl_fd("42sh: Internal Malloc Error", STDERR_FILENO);
			return (DROP_PROCESS);
		}
		val_len = ft_strlen(proc->argv[0]) - ft_strlen(name) - 1;
		if (!(value = ft_strsub(proc->argv[0], ft_strlen(name) + 1, val_len)))
			return (DROP_PROCESS);
		if (list_manager(VAR_ADD, new_var(name, value, proc), env) == -1)
			break ;
		if (proc->argv[0] == NULL)
			return (update_dropped_process_informations(proc, env));
	}
	list_manager(VAR_PUSH_TMP, NULL, env);
	return (CONTINUE_PROCESS);
}
