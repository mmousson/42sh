/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_get_user_home.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 22:56:44 by mmousson          #+#    #+#             */
/*   Updated: 2019/10/05 11:01:19 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pwd.h>
#include "libft.h"
#include "sh42.h"

#ifdef __linux__

/*
**	This functions returns the Path to the HOME directory associated with
**	the current USER ID
**	Simply gets the user definition from /etc/passwd associated with the
**	current effective user ID
**	Once it has been done, exctract the HOME dir from this definition
**	The returned (char *) is a freshly allocated string
**	No error handling is needed since 'geteuid' syscall can't fail
**
**	Arguments: NONE
**
**	Return Value: The path the HOME directory of the user
*/

char	*utility_get_user_home(void)
{
	struct passwd	*user_pwd;

	user_pwd = getpwuid(geteuid());
	if (user_pwd != NULL)
		return (ft_strdup(user_pwd->pw_dir));
	else
		return (NULL);
}

#else

/*
**	This functions returns the Path to the HOME directory associated with
**	the current logged in user
**	Simply gets the effective user login with the 'getlogin' call
**	Once it has been done, translates this login into the corresponding
**	HOME dir with 'getpwnam'
**	'getlogin' CAN and MAY fail, and if so, a default value of '/tmp/' will
**	be used as a HOME directory for the current session
**
**	Arguments: NONE
**
**	Return Value: The path the HOME directory of the user
*/

char	*utility_get_user_home(void)
{
	char			*login;
	struct passwd	*user_pwd;

	login = getlogin();
	if (login == NULL || *login == '\0')
	{
		ft_putendl_fd("42sh: getlogin error, using default HOME value: /tmp/",
			STDERR_FILENO);
		return (ft_strdup("/tmp/"));
	}
	else if (ft_strequ(login, "_cvmsroot"))
	{
		ft_putendl_fd("42sh: getlogin returned default account '_cvmsroot'"
			", HOME value set to default: /tmp/", 2);
		return (ft_strdup("/tmp/"));
	}
	user_pwd = getpwnam(login);
	if (user_pwd != NULL)
		return (ft_strdup(user_pwd->pw_dir));
	else
		return (NULL);
}

#endif

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

char	*utility_get_aliases_file_full_path(void)
{
	char	*user_home;
	char	*alias_file;

	if ((user_home = utility_get_user_home()) == NULL)
	{
		ft_putendl_fd("42sh: Error: Effective USER ID invalid", STDERR_FILENO);
		return (NULL);
	}
	if ((alias_file = ft_strjoin(user_home, ALIAS_FILE)) == NULL)
		ft_putendl_fd("42sh: Internal malloc error", STDERR_FILENO);
	ft_strdel(&user_home);
	return (alias_file);
}
