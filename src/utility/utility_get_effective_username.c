/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_get_effective_username.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 06:17:23 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/20 11:45:35 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	This functions returns the Path to the HOME directory associated with
**	the current USER ID
**	Simply gets the effective user ID of the calling process
**	with the 'geteuid' system call
**	Once it has been done, translates this ID into the corresponding username
*/

char	*utility_get_effective_user_name(void)
{
	struct passwd	*user_pwd;
	uid_t			user_id;

	if ((user_id = geteuid()) == (uid_t)-1)
	{
		write(STDERR_FILENO, "geteuid Undefined Error", 23);
		return (NULL);
	}
	else
	{
		user_pwd = getpwuid(user_id);
		if (user_pwd != NULL)
			return (ft_strdup(user_pwd->pw_name));
		else
			return (NULL);
	}
}
