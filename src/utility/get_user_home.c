/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_user_home.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 22:56:44 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/14 05:01:52 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pwd.h>
#include <unistd.h>
#include <uuid/uuid.h>
#include <sys/types.h>

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

	if ((user_id = geteuid()) == -1)
	{
		write(STDERR_FILENO, "geteuid Undefined Error", 23);
		return(NULL);
	}
	else
		return (getpwuid(user_id)->pw_dir);
}
