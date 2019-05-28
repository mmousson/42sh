/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_chmod.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 08:48:11 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/28 08:48:13 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

int			auto_chmod(int index, char **name, char **desc)
{
	static char	*flag_tab[21] = {
		"-C", "-E", "-H", "-I", "-L", "-N", "-P", "R", "-f", "-h", "-i",
		"-v", " X", " g", " o", " r", " s", " t", " u", " w", " x"};
	static char	*desc_tab[21] = {
		"  -- returns false if any of the named files have ACLs",
		"  -- read ACL info from stdin as a sequential list of ACEs",
		"  -- follow symlinks on the command line",
		"  -- removes all inherited entries from named files ACLs",
		"  -- follow all symlinks",
		"  -- remove ACLs from specified files",
		"  -- do not follow symlinks (default)",
		"  -- change files and directories recursively",
		"  -- suppress most error messages",
		"  -- operate on symlinks them self",
		"  -- removes inherited bit from all entries in named files ACLs",
		"  -- output a diagnostic for every file processed",
		"  -- execute only if directory or executable to another",
		"  -- group's current permissions",
		"  -- other's current permissions", "  -- read",
		"  -- set uid/gid", "  -- sticky",
		"  -- owner's current permissions", "  -- write", "  -- execute"};

	*name = ft_strdup(flag_tab[index]);
	*desc = ft_strdup(desc_tab[index]);
	return (21);
}
