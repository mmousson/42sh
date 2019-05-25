/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_generate_tmp_filename.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 10:20:08 by mmousson          #+#    #+#             */
/*   Updated: 2019/05/25 10:45:33 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "libft.h"

/*
**	Generates a new permutation of the filename, which will then be used to
**	check if that combination points to an already existing file
**
**	Arguments:
**	base -> The current combination
**	new_suffix -> The new number of the file
**
**	Return Value:
**	NULL -> A malloc error occured
**	NON-NULL -> The next permutation
*/

static char	*next_permutation(const char *base, char new_suffix)
{
	size_t	len;
	char	*new;

	len = ft_strlen(base);
	if ((new = ft_strnew(len + (new_suffix == '0' + 10))) == NULL)
	{
		ft_putendl_fd("42sh: Internal Malloc Error", STDERR_FILENO);
		return (NULL);
	}
	ft_strcpy(new, base);
	if (new_suffix == '0' + 10)
	{
		new[len - 1] = '_';
		new[len] = '1';
	}
	else
		new[len - 1] = new_suffix;
	return (new);
}

/*
**	Function that generates a valid and available filename in order for it to
**	be used as a temporary file (heredoc AND/OR substitutions)
**	It generates a path with a base '.tmp' followed by a '_' padding and a
**	number
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

char		*utility_generate_filename(void)
{
	char	*res;
	char	*tmp;
	int		i;

	if ((res = ft_strdup(".tmp_")) != NULL)
	{
		i = 0;
		while (42)
		{
			if ((tmp = next_permutation(res, '0' + i)) == NULL)
				return (NULL);
			ft_strdel(&res);
			res = tmp;
			if (!utility_file_exists(res))
				return (res);
			i %= 10;
			i++;
		}
	}
	else
	{
		ft_putendl_fd("42sh: Internal Malloc Error", STDERR_FILENO);
		return (NULL);
	}
}
