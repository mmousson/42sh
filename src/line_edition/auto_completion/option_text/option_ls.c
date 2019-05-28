/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 08:49:39 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/28 09:16:53 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

static char		*auto_get_lsdesc_next(int index)
{
	static char	*desc_tab[14] = {
		"  -- print file inode numbers", "  -- print sizes of 1k",
		"  -- long listing", "  -- comma separated", "  -- numeric uid, gid",
		"  -- display file flags",
		"  -- append file type indicators for directory",
		"  -- hide control chars", "  -- reverse sort order",
		"  -- display size of each file in blocks",
		"  -- sort by modification time",
		"  -- access time", "  -- print raw characters",
		"  -- sort horizontally"};

	return (ft_strdup(desc_tab[index]));
}

static char		*auto_get_lsdesc(int index)
{
	static char	*desc_tab[18] = {
		"  -- single column output", "  -- list all except . and ..",
		"  -- print octal escapes for control characters",
		"  -- list entries in columns sorted vertically",
		"  -- append file type indicators",
		"  -- follow symlinks on the command line",
		"  -- list referenced file for sym link",
		"  -- do not follow symlinks", "  -- list subdirectories recursively",
		"  -- sort by size", "  -- show complete time information",
		"  -- list entries starting with .",
		"  -- as -B, but use C escape codes whenever possible",
		"  -- status change time",
		"  -- list directory entries instead of contents",
		"  -- output is not sorted",
		"  -- long listing but without owner information",
		"  -- print sizes in human readable form"};

	if (index > 17)
		return (auto_get_lsdesc_next(index - 18));
	return (ft_strdup(desc_tab[index]));
}

int				auto_ls(int index, char **name, char **desc)
{
	static char	*flag_tab[32] = {
		"-1", "-A", "-B", "-C", "-F", "-H", "-L", "-P", "-R", "-S", "-T", "-a",
		"-b", "-c", "-d", "-f", "-g", "-h", "-i", "-k", "-l", "-m", "-n", "-o",
		"-p", "-q", "-r", "-s", "-t", "-u", "-w", "-x"};

	*name = ft_strdup(flag_tab[index]);
	*desc = auto_get_lsdesc(index);
	return (32);
}
