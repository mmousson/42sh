/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_environ_utilities.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 02:45:10 by mmousson          #+#    #+#             */
/*   Updated: 2019/05/14 07:56:12 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "libft.h"

/*
**
*/

static int	ft_key_index(char **environ, char *key)
{
	int		res;
	size_t	key_len;

	if (environ == NULL || key == NULL)
		return (0);
	res = 0;
	key_len = ft_strlen(key);
	while (environ[res] != NULL && ft_strncmp(environ[res], key, key_len) != 0)
		res++;
	return (res);
}

/*
**
*/

static int	ft_expand(char ***environ)
{
	int		i;
	int		count;
	char	**new;

	if (environ == NULL || *environ == NULL)
		return (-1);
	i = -1;
	count = utility_get_environ_length(*environ) + 1;
	if ((new = (char **)ft_memalloc(sizeof(char *) * (count + 2))) == NULL)
		return (-1);
	while (++i < count)
		new[i] = (*environ)[i];
	new[i - 1] = NULL;
	new[i] = NULL;
	free(*environ);
	*environ = new;
	return (i - 1);
}

/*
**
*/

void		utility_add_entry_to_environ(char ***environ, char *key, char *value)
{
	int		where;
	char	*tmp;

	if (environ == NULL || *environ == NULL || key == NULL || value == NULL)
		return ;
	if (utility_get_env_var(environ, key) == NULL)
	{
		if ((tmp = ft_strjoin(key, "=")) != NULL
			&& (where = ft_expand(environ)) != -1)
			(*environ)[where] = ft_strjoin(tmp, value);
		else
			ft_putendl_fd("42sh: Internal Malloc Error", STDERR_FILENO);
		ft_strdel(&tmp);
	}
	else
	{
		where = ft_key_index(*environ, key);
		tmp = ft_strjoin(key, "=");
		ft_strdel(&((*environ)[where]));
		if (environ && *environ)
			(*environ)[where] = ft_strjoin(tmp, value);
		free(tmp);
	}
}

/*
**
*/

int			utility_rm_entry_from_environ(char ***environ, char *key)
{
	int		i;
	size_t	key_len;
	char	**env;
	char	*tmp;

	if (environ == NULL || *environ == NULL || key == NULL)
		return (0);
	i = -1;
	env = *environ;
	key_len = ft_strlen(key);
	while (env[++i] != NULL)
		if (ft_strncmp(env[i], key, key_len) == 0)
		{
			ft_memdel((void **)&(env[i]));
			while (env[++i] != NULL)
			{
				tmp = env[i - 1];
				env[i - 1] = ft_strdup(env[i]);
				ft_memdel((void **)(&tmp));
			}
			ft_memdel((void **)&(env[i - 1]));
			return (0);
		}
	*environ = env;
	return (1);
}

/*
**
*/

char		**utility_duplicate_environ(char **env)
{
	int		i;
	int		length;
	char	**res;

	i = -1;
	if ((length = utility_get_environ_length(env)) == -1)
		return (NULL);
	if ((res = (char **)ft_memalloc(sizeof(char *) * (length + 1))) == NULL)
	{
		ft_putendl_fd("42sh: Internal Malloc Error", STDERR_FILENO);
		return (NULL);
	}
	while (++i < length)
	{
		if ((res[i] = ft_strdup(env[i])) == NULL)
		{
			while (--i >= 0)
				ft_strdel(&(res[i]));
			ft_memdel((void **)&(res));
			ft_putendl_fd("42sh: Internal Malloc Error", STDERR_FILENO);
			return (NULL);
		}
	}
	res[i] = NULL;
	return (res);
}
