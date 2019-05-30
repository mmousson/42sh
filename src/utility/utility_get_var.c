/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_get_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 04:57:56 by mmousson          #+#    #+#             */
/*   Updated: 2019/05/30 22:39:57 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh42.h"

/*
**	We first look for the variable name in the TMP table
**
**	Arguments:
**	name -> The name of the variable we are looking for
**	env -> The shell's current temporary variables array
**
**	Return Value:
**	NULL -> The variable doesn't exist
**	NON-NULL -> The value of the variable designated by 'name'
*/

static char	*get_var_from_temporary_table(char *name)
{
	t_vars	*current;

	current = g_shell_tmp_vars;
	while (current != NULL)
	{
		if (ft_strequ(name, current->name))
			return (ft_strdup(current->value));
		current = current->next;
	}
	return (NULL);
}

/*
**	If the variable doesn't exist in the shell's tempoarary table
**	then we try to retrieve it from the linked list 'g_shell_var_list'
**
**	Arguments:
**	name -> The name of the variable we are looking for
**	env -> The shell's current environment array
**
**	Return Value:
**	NULL -> The variable doesn't exist
**	NON-NULL -> The value of the variable designated by 'name'
*/

static char	*get_var_from_environment(char *name, char **env)
{
	int		i;
	size_t	name_len;

	i = -1;
	name_len = ft_strlen(name);
	while (env[++i] != NULL)
	{
		if (ft_strnequ(name, env[i], name_len) && env[i][name_len] == '=')
			return (ft_strdup(env[i] + name_len + 1));
	}
	return (NULL);
}

/*
**	If the variable doesn't exist in the shell's environment, we try to
**	retrieve it from the linked list 'g_shell_var_list'
**
**	Arguments:
**	name -> The name of the variable we are looking for
**	env -> The shell's current environment array
**
**	Return Value:
**	NULL -> The variable doesn't exist
**	NON-NULL -> The value of the variable designated by 'name'
*/

static char	*get_var_from_internal_definitions(char *name)
{
	t_vars	*current;

	current = g_shell_var_list;
	while (current != NULL)
	{
		if (ft_strequ(name, current->name))
			return (ft_strdup(current->value));
		current = current->next;
	}
	return (NULL);
}

/*
**	This wrapper function returns the value, if it exists, of the variable
**	designated by 'name'
**	It searches both in the environment and in the shell's linked list
**	'g_shell_var_list'
**
**	Arguments:
**	name -> The name of the variable we are looking for
**	env -> The shell's current environment array
**
**	Return Value:
**	NULL -> The variable doesn't exist
**	NON-NULL -> The value of the variable designated by 'name'
*/

char		*utility_get_var(char *name, char **env)
{
	char	*res;

	if ((res = get_var_from_temporary_table(name)) != NULL
		||(res = get_var_from_environment(name, env)) != NULL
		|| (res = get_var_from_internal_definitions(name)) != NULL)
		return (res);
	else
		return (NULL);
}
