/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_set_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 06:20:40 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/05 02:02:36 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "sh42.h"

/*
**	This simple function generates a string holding the information given by
**	'name' and 'value' in the form:
**	%s=%s, name, value
**	In case of memory allocation error, NULL is returned
**
**	Arguments:
**	name -> First part of the string
**	value -> Second part of the string
**
**	Return Value:
**	NULL -> A memory allocation failed
**	NON-NULL -> The generated string
*/

static char	*generate_env_definition(char *name, char *value)
{
	char	*tmp;
	char	*res;

	res = NULL;
	if ((tmp = ft_strjoin(name, "=")) != NULL)
	{
		if ((res = ft_strjoin(tmp, value)) == NULL)
			ft_putendl_fd("42sh: Internal Malloc Error", STDERR_FILENO);
	}
	else
		ft_putendl_fd("42sh: Internal Malloc Error", STDERR_FILENO);
	ft_strdel(&tmp);
	return (res);
}

/*
**	First function to be called by the 'utility_set_var' wrapper function
**	It searches for a variable designed by 'name' in the 'env' array
**	If found, it will replace that array element by a new one, with the
**	same name, but with the 'value' content in the form:
**	%s=%s\n, name, value
**	In case of memory allocation error, nothing is modified in the 'env' array
**
**	Arguments:
**	name -> The name of the variable to replace, if it exists in env
**	value -> The new content of the variable 'name', if it exists in env
**	env -> The shell's current environment array
**
**	Return Value:
**	0 -> A variable designed by 'name' doesn't exist in the 'env' array
**	1 -> The variable designed by 'name' was found in the 'env' array
**		and its content was replaced by 'value'
*/

static int	set_already_existing_env_var(char *name, char *value, char **env)
{
	int		i;
	size_t	name_len;
	char	*tmp;

	i = -1;
	name_len = ft_strlen(name);
	while (env[++i] != NULL)
	{
		if (ft_strnequ(name, env[i], name_len) && env[i][name_len] == '=')
		{
			if ((tmp = generate_env_definition(name, value)) == NULL)
				ft_putendl_fd("42sh: Internal Malloc Error", STDERR_FILENO);
			else
			{
				ft_strdel(&(env[i]));
				env[i] = tmp;
			}
			return (1);
		}
	}
	return (0);
}

/*
**	Second function to be called by the 'utility_set_var' wrapper function
**	It searches for a variable definition with the name 'name' in the
**	'g_shell_var_list' linked list
**	If found, it replaces its field 'value' by the 'value' argument
**	In case of memory allocation error, the link is remove from the list
**	and all the memory it occupies is free'd
**
**	Arguments:
**	name -> The name of the variable to look for in the 'g_shell_var_list'
**	value -> The replacement value of the wanted variable definition
**
**	Return Value:
**	0 -> A variable designed by 'name' doesn't exist in the linked list
**	1 -> The variable designed by 'name' was found in the linked list
**		and its content field was replaced by 'value'
*/

static int	set_already_existing_internal_var(char *name, char *value)
{
	t_vars	*prev;
	t_vars	*current;

	prev = NULL;
	current = g_shell_var_list;
	while (current != NULL)
	{
		if (ft_strequ(name, current->name))
		{
			ft_strdel(&current->value);
			if ((current->value = ft_strdup(value)) == NULL)
			{
				ft_putendl_fd("42sh: Internal Malloc Error", STDERR_FILENO);
				(prev != NULL) ? prev->next = current->next : (0);
				if (prev == NULL)
					g_shell_var_list = current->next;
				ft_strdel(&current->value);
				ft_memdel((void **)&(current));
			}
			return (1);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}

/*
**	Function specifically designed to delete an internal variable definiton
**	except its 'value' field which is saved for being returned afterwards
**	It will then be free'd by the calling function right after usage
**
**	Arguments:
**	name -> The name of the variable we are looking for
**
**	Return Value:
**	NULL -> There are no internal variable with such name, nothing was deleted
**	NON-NULL -> The 'value' field of the deleted internal var definition
*/

static char	*delete_internal_var_and_get_value(char *name)
{
	char	*ret;
	t_vars	*holder;
	t_vars	*holder_next;

	if ((ret = utility_internal_var_exists(name, &holder)) != NULL)
	{
		holder_next = holder->next;
		if (holder_next != NULL)
			holder_next->prev = holder->prev;
		if (holder->prev != NULL)
			holder->prev->next = holder_next;
		ft_strdel(&holder->name);
		ret = holder->value;
		ft_memdel((void **)&(holder));
	}
	return (ret);
}

/*
**	This functions sets a variable in the current shell's environment or as an
**	internal variable
**	It does so by modifying an already existing defintion or creating a new one
**	when appropriate
**	It first checks if such a definition with the same name already exists in
**	the environment and if so, modifies it
**	If not, it then searches a defintion with the same name in the internal
**	variables list and if so, modifies it
**	If both condition are not met, it creates a freshly new definition and
**	prepends it to the 'g_shell_var_list'
**
**	Arguments:
**	name -> The name of the variable we want to set
**	value -> The value of the variable we want to set
**	env -> A pointer to the shell's current environment
**
**	Return Value: NONE
*/

void		utility_set_var(char *name, char *value, char ***env, int export_var)
{
	char	*tmp;

	if (name == NULL || env == NULL)
		return ;
	if (export_var)
	{
		tmp = delete_internal_var_and_get_value(name);
		utility_add_entry_to_environ(env, name, value ? value : tmp);
		ft_strdel(&tmp);
	}
	else if (value != NULL)
	{
		if (set_already_existing_env_var(name, value, *env) == 1
			|| set_already_existing_internal_var(name, value) == 1)
			return ;
		else
			utility_add_internal_var(name, value);
	}
}
