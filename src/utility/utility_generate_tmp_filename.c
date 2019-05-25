/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_generate_tmp_filename.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 10:20:08 by mmousson          #+#    #+#             */
/*   Updated: 2019/05/25 11:07:29 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/random.h>
#include "sh42.h"
#include "libft.h"

/*
**	Generates a new permutation of the filename, which will then be used to
**	check if that combination points to an already existing file
**
**	Arguments:
**	base -> The current combination
**
**	Return Value:
**	NULL -> A malloc error occured
**	NON-NULL -> The next permutation
*/

static char	*next_permutation(const char *base)
{
	size_t	len;
	char	*new;
	char	next_suffix;

	len = ft_strlen(base);
	if ((new = ft_strnew(len + 1)) == NULL)
	{
		ft_putendl_fd("42sh: Internal Malloc Error", STDERR_FILENO);
		return (NULL);
	}
	ft_strcpy(new, base);
	getentropy(&next_suffix, 1);
	new[len] = (ft_abs(next_suffix) % 40) + 42;
	return (new);
}

/*
**	Function that generates a valid and available filename in order for it to
**	be used as a temporary file (heredoc AND/OR substitutions)
**	It generates a path with a base '.tmp' followed by a new random character
**		each time
**	Each generated combination is then used to verify whether a file pointed
**	by 'res' already exists and if not, the result is returned
**
**	Arguments: NONE
**
**	Return Value:
**	NULL -> A malloc error occured
**	NON-NULL -> The name of a file that doesn't already exist and can be safely
**		created and used
*/

char		*utility_generate_tmp_filename(void)
{
	char	*res;
	char	*tmp;

	if ((res = ft_strdup(".tmp_")) != NULL)
	{
		while (42)
		{
			if ((tmp = next_permutation(res)) == NULL)
				return (NULL);
			printf("Got: %s\n", tmp);
			usleep(60000);
			ft_strdel(&res);
			res = tmp;
			if (!utility_file_exists(res))
				return (res);
		}
	}
	else
	{
		ft_putendl_fd("42sh: Internal Malloc Error", STDERR_FILENO);
		return (NULL);
	}
}
