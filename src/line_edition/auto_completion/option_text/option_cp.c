/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_cp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 08:48:19 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/28 09:21:41 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

int					auto_cp(int index, char **name, char **desc)
{
	static char		*flag_tab[11] = {
		"-H", "-L", "-P", "-R", "-X", "-a", "-f", "-i", "n", "-p", "-v"};
	static char		*desc_tab[11] = {
		"  -- follow symlinks on the command line in recursive mode",
		"  -- follow all symlinks in recursive mode",
		"  -- do not follow symlinks in recursive mode (default)",
		"  -- copy directories recursively",
		"  -- don't copy extended attributes or resource forks",
		"  -- archive mode, same as -RpP",
		"  -- force overwriting existing file",
		"  -- confirm before overwriting existing file",
		"  -- don't overwrite existing file",
		"  -- preserve timestamps, mode, owner, flags, ACLs, and ext attrib",
		"  -- show file names as they are copied"};

	*name = ft_strdup(flag_tab[index]);
	*desc = ft_strdup(desc_tab[index]);
	return (11);
}
