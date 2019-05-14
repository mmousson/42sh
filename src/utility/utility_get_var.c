/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_get_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 04:57:56 by mmousson          #+#    #+#             */
/*   Updated: 2019/05/14 05:07:34 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh42.h"

static char *get_var_from_environment(char *name, char ***env)
{
	int		i;
	size_t	name_len;

	i = -1;
	name_len = ft_strlen(name);
	while ((*env)[++i] != NULL)
	{
		if (ft_strnequ(name, (*env)[i], name_len) && (*env)[i][name_len] == '=')
			return (ft_strdup((*env)[i] + name_len + 1));
	}
	return (NULL);
}

static char *get_var_from_internal_definitions(char *name)
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

char        *utility_get_var(char *name, char ***env)
{
    char    *res;

    if ((res = get_var_from_environment(name, env)) != NULL
        || (res = get_var_from_internal_definitions(name)) != NULL)
        return (res);
    else
        return (NULL);
}