/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 04:14:48 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/10 13:26:18 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
//#include <sys/wait.h>
#include <sys/stat.h>

int					is_exec(char *path)
{
	struct stat		data;
	int				ret;

	if ((ret = stat(path, &data)) == -1)
		return (0);
	if (ret == 0 && data.st_mode & S_IXUSR && !S_ISDIR(data.st_mode))
		return (1);
	return (0);
}
