/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_getstatinfo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 12:34:55 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/30 15:01:34 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"
#include <sys/stat.h>
#include <unistd.h>

static int			auto_attribute_statvalue(char c, int ret, char **path,
		char *carac)
{
	*carac = c;
	ft_strdel(path);
	return (ret);
}

int					auto_getstatype(char *name, char *carac, int index)
{
	struct stat		m_stat;
	char			*path;
	char			*exp;

	if (!(path = ft_strjoin(g_data.path[index], name)))
		sh_errorterm(TMALLOC);
	exp = auto_expand(&path);
	ft_strdel(&path);
	if (lstat(exp, &m_stat) == -1)
		;
	else if (S_ISLNK(m_stat.st_mode))
		return (auto_attribute_statvalue('@', 14, &exp, carac));
	else if (S_ISDIR(m_stat.st_mode))
		return (auto_attribute_statvalue('/', 9, &exp, carac));
	else if (m_stat.st_mode & S_IXUSR)
		return (auto_attribute_statvalue('*', 10, &exp, carac));
	else if (S_ISCHR(m_stat.st_mode))
		return (auto_attribute_statvalue('%', 11, &exp, carac));
	else if (S_ISBLK(m_stat.st_mode))
		return (auto_attribute_statvalue('#', 11, &exp, carac));
	else if (S_ISFIFO(m_stat.st_mode))
		return (auto_attribute_statvalue('|', 3, &exp, carac));
	ft_strdel(&exp);
	return (7);
}
