/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 11:23:46 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/16 12:16:45 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

/*
**
*/

int	check_type(const char *pathname, const int bitmask)
{
	struct stat	sb;

	if (lstat(pathname, &sb) == -1)
		return (TEST_FALSE);
	if (bitmask == IGNORE_TYPE)
		return (TEST_TRUE);
	else if (bitmask == CHECK_SIZE)
		return (sb.st_size > 0 ? TEST_TRUE : TEST_FALSE);
	if (bitmask != S_IFLNK && (sb.st_mode & S_IFMT) == S_IFLNK)
		stat(pathname, &sb);
	if (bitmask == R_OK || bitmask == W_OK || bitmask == X_OK)
	{
		if (access(pathname, bitmask) != -1)
			return (TEST_TRUE);
		else
			return (TEST_FALSE);
	}
	else
		return ((sb.st_mode & S_IFMT) == bitmask ? TEST_TRUE : TEST_FALSE);
}
