/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_alias_list_to_file.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 04:35:48 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/14 05:05:29 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include "libft.h"
#include "sh42.h"

/*
**	This function conputes the Full and Absolute path to the aliases file
**	in the user's HOME directory
**
**	Arguments: NONE
**
**	Return Value:
**	NULL -> A malloc failed or the user's effective USER ID is invalid
**	NON-NULL -> A char * pointer to the actual full path towards the
**		'.42sh_aliases' file. Everything went well
*/

static char	*get_aliases_file_full_path(void)
{
	char	*user_home;
	char	*alias_file;

	if ((user_home = get_user_home()) == NULL)
		return (NULL);
	alias_file = ft_strjoin(user_home, ALIAS_FILE);
	return (alias_file);
}

/*
**	This function will write down every alias definiton hold in the current
**	shell execution environment
**	These definition will be put in a file named '.42sh_aliases' at the root
**	of the user's HOME directory
**	The path of this file is computed by the func 'get_aliases_file_full_path'
**	defined above
**	Aliases definitons are then written down in the form :
**	%s=%s\n, token, replacement
**
**	Arguments: NONE
**
**	Return Value: NONE
*/

void		write_alias_list_to_file(void)
{
	int		fd;
	char	*alias_file;
	t_alias	*current;

	if ((alias_file = get_aliases_file_full_path()) == NULL)
	{
		ft_putendl_fd("42sh: Error: Effective USER ID invalid", STDERR_FILENO);
		return ;
	}
	fd = open(alias_file, O_CREAT | O_RDWR, 0644);
	ft_strdel(&alias_file);
	if (fd == -1)
	{
		ft_putendl_fd("42sh: Error: could not open alias file", STDERR_FILENO);
		return ;
	}
	current = alias_list;
	while (current)
	{
		ft_putstr_fd(current->token, fd);
		ft_putchar_fd('=', fd);
		ft_putendl_fd(current->replacement, fd);
		current = current->next;
	}
	close(fd);
}
