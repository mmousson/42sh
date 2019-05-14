/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_set_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 06:20:40 by mmousson          #+#    #+#             */
/*   Updated: 2019/05/14 06:04:10 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	ft_strdel(&res);
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
			ft_strdel(&current->name);
			if ((current->name = ft_strdup(value)) == NULL)
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
**	In case both of the function above return 0 (which means the variable
**	designed by 'name' doesn't exist yet), this function is called by the
**	'utility_set_var' wrapper function
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

static void	add_var(char *name, char *value)
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
			internal->next = g_shell_var_list;
			g_shell_var_list = internal;
		}
	}
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

void		utility_set_var(char *name, char *value, char **env)
{
	if (name == NULL || value == NULL || env == NULL)
		return ;
	if (set_already_existing_env_var(name, value, env) == 1)
		return ;
	else if (set_already_existing_internal_var(name, value) == 1)
		return ;
	else
		add_var(name, value);
}
