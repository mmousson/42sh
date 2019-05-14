/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_set_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 06:20:40 by mmousson          #+#    #+#             */
/*   Updated: 2019/05/14 04:56:08 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "sh42.h"

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

static int	set_already_existing_env_var(char *name, char *value, char ***env)
{
	int		i;
	size_t	name_len;
	char	*tmp;

	i = -1;
	name_len = ft_strlen(name);
	while ((*env)[++i] != NULL)
	{
		if (ft_strnequ(name, (*env)[i], name_len) && (*env)[i][name_len] == '=')
		{
			if ((tmp = generate_env_definition(name, value)) == NULL)
				ft_putendl_fd("42sh: Internal Malloc Error", STDERR_FILENO);
			else
			{
				ft_strdel(&((*env)[i]));
				(*env)[i] = tmp;
			}
			return (1);
		}
	}
	return (0);
}

static int	set_already_existing_internal_var(char *name)
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
			if ((current->name = ft_strdup(name)) == NULL)
			{
				ft_putendl_fd("42sh: Internal Malloc Error", STDERR_FILENO);
				if (prev != NULL)
					prev->next = current->next;
				else
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

void		utility_set_var(char *name, char *value, char ***env)
{
	if (name == NULL || value == NULL || env == NULL)
		return ;
	if (set_already_existing_env_var(name, value, env) == 1)
		return ;
	else if (set_already_existing_internal_var(name) == 1)
		return ;
	else
		add_var(name, value);
}
