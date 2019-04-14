/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_user_home.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 22:56:44 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/14 05:44:57 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pwd.h>
#include <unistd.h>
#include <uuid/uuid.h>
#include <sys/types.h>
#include "libft.h"
#include "sh42.h"

/*
**	This functions returns the Path to the HOME directory associated with
**	the current USER ID
**	Simply gets the effective user ID of the calling process
**	with the 'geteuid' system call
**	Once it has been done, translates this ID into the corresponding HOME dir
*/

char	*get_user_home(void)
{
	struct passwd	*user_pwd;
	uid_t			user_id;

	if ((user_id = geteuid()) == (uid_t)-1)
	{
		write(STDERR_FILENO, "geteuid Undefined Error", 23);
		return(NULL);
	}
	else
	{
		user_pwd = getpwuid(user_id);
		if (user_pwd != NULL)
			return (user_pwd->pw_dir);
		else
			return (NULL);
	}
}

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

char	*get_aliases_file_full_path(void)
{
	char	*user_home;
	char	*alias_file;

	if ((user_home = get_user_home()) == NULL)
	{
		ft_putendl_fd("42sh: Error: Effective USER ID invalid", STDERR_FILENO);
		return (NULL);
	}
	if ((alias_file = ft_strjoin(user_home, ALIAS_FILE)) == NULL)
		ft_putendl_fd("42sh: Internal malloc error", STDERR_FILENO);
	return (alias_file);
}
