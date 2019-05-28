/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_df.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 08:48:39 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/28 08:48:40 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

int			auto_df(int index, char **name, char **desc)
{
	static char	*flag_tab[13] = {
		"-H", "-P", "-T", "-a", "-b", "c", "-g", "h", "-i", "-k", "-l",
		"-m", "-n"};
	static char	*desc_tab[13] = {
		"  -- human-readable output (base 10)",
		"  -- POSIX compliant output",
		"  -- only display file systems of specified types",
		"  -- show all mount points",
		"  -- use 512-byte blocks (default)",
		"  -- display a grand total",
		"  -- use 1024^3-byte blocks",
		"  -- human-readable output (base 2)",
		"  -- include inode usage statistics (default)",
		"  -- use 1024-byte blocks",
		"  -- only display locally-mounted file systems",
		"  -- use 1024*1024-byte blocks",
		"  -- use previously obtained statistics"};

	*name = ft_strdup(flag_tab[index]);
	*desc = ft_strdup(desc_tab[index]);
	return (13);
}
