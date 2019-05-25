/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_file_exists.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 21:32:46 by mmousson          #+#    #+#             */
/*   Updated: 2019/05/25 11:28:05 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/stat.h>

/*
**	Utility function to check whether a file pointed by 'path' exists
**
**	Arguments:
**	path -> The file we want to check the existence of
**
**	Return Value:
**	0 -> The file doesn;t exist
**	1 -> The file exists
*/

int	utility_file_exists(const char *path)
{
	struct stat	buffer;

	if (path == NULL)
		return (0);
	return (stat(path, &buffer) == 0);
}
