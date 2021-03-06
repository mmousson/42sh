/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_write_alias_list_to_file.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 04:35:48 by mmousson          #+#    #+#             */
/*   Updated: 2019/05/25 06:45:50 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"
#include "sh42.h"

/*
**	This function will write down every alias definiton hold in the current
**	shell execution environment
**	These definition will be put in a file named '.42sh_aliases' at the root
**	of the user's HOME directory
**	The path of this file is computed by the func
**	'utility_get_aliases_file_full_path' defined above
**	Aliases definitons are then written down in the form :
**	%s=%s\n, token, replacement
**
**	Arguments: NONE
**
**	Return Value: NONE
*/

void		utility_write_alias_list_to_file(void)
{
	int		fd;
	char	*alias_file;
	t_alias	*current;

	if ((alias_file = utility_get_aliases_file_full_path()) == NULL)
		return ;
	fd = open(alias_file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	ft_strdel(&alias_file);
	if (fd == -1)
	{
		ft_putendl_fd("42sh: Error: could not open alias file", STDERR_FILENO);
		return ;
	}
	current = g_alias_list;
	while (current)
	{
		ft_putstr_fd(current->token, fd);
		ft_putchar_fd('=', fd);
		ft_putendl_fd(current->replacement, fd);
		current = current->next;
	}
	close(fd);
}
