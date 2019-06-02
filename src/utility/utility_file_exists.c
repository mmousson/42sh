/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_file_exists.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 21:32:46 by mmousson          #+#    #+#             */
/*   Updated: 2019/05/31 15:34:13 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/stat.h>
#include "sh42.h"

/*
**	Utility function to check whether a file pointed by 'path' exists
**
**	Arguments:
**	path -> The file we want to check the existence of
**
**	Return Value:
**	0 -> The file doesn;t exist
**	!= 0 -> The file exists and a Macro corresponding to the file type has
**		been returned
*/

int	utility_file_exists(const char *path)
{
	struct stat	buffer;

	if (path == NULL)
		return (0);
	if (stat(path, &buffer) != 0)
		return (0);
	else
	{
		if (S_ISDIR(buffer.st_mode))
			return (FILETYPE_DIRECTORY);
		else
			return (FILETYPE_REGULAR);
	}
}
