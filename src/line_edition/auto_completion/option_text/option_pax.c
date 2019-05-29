/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_pax.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 08:55:55 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/28 09:17:24 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

static char			*auto_get_paxdesc(int index)
{
	static char		*desc_tab[20] = {
		"  -- ignore older files by ctime",
		"  -- follow only command-line symlinks",
		"  -- follow all symlinks",
		"  -- do not follow symlinks",
		"  -- do not descend into directories that have a different device ID",
		"  -- ignore older files by ctime after file name mods",
		"  -- ignore older files after file name mods",
		"  -- append", "  -- match all but specified",
		"  -- match only directory but not contents",
		"  -- interactively rename files", "  -- filter archive through bzip2",
		"  -- do not overwrite existing files", "  -- hardlink files",
		"  -- select only the first match for each pattern", "  -- read",
		"  -- reset access times of files after access",
		"  -- ignore older files", "  -- verbose", "  -- write"};

	return (ft_strdup(desc_tab[index]));
}

int					auto_pax(int index, char **name, char **desc)
{
	static char		*flag_tab[31] = {
		"-D", "-H", "-L", "-P", "-X", "-Y", "-Z", "-a", "-c",
		"-d", "-i", "-j", "-k", "-l", "-n", "-r", "-t", "-u",
		"-v", "-w", "-B", "-E", "-G", "-T", "-U", "-b", "-f",
		"-o", "-p", "-s", "-x"};

	*name = ft_strdup(flag_tab[index]);
	if (index < 20)
		*desc = auto_get_paxdesc(index);
	else
		*desc = ft_strdup(" ");
	return (31);
}
