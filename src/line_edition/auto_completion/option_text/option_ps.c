/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_ps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 08:56:00 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/28 09:17:41 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

static char			*auto_get_psdesc(int index)
{
	static char		*desc_tab[27] = {
		"  -- select every process",
		"  -- ignore resident time for CPU percentage",
		"  -- select processes by real group",
		"  -- show threads as if they were processes",
		"  -- display all format specifiers",
		"  -- extract values from specified core",
		"  -- set namelist file for WCHAN display",
		"  -- specify additional output fields",
		"  -- include child process data with the parent",
		"  -- select processes attached to current terminal",
		"  -- select processes by effective user", "  -- show security data",
		"  -- include processes belonging to other users",
		"  -- show just executable name for command",
		"  -- show environment after command",
		"  -- repeat header lines, one per page of output",
		"  -- output in job control format", "  -- output in long format",
		"  -- sort by memory usage", "  -- specify output format",
		"  -- select processes by ID", "  -- sort by CPU usage",
		"  -- select processes by attached terminal",
		"  -- output in resource usage format",
		"  -- output in virtual memory format", "  -- wide output",
		"  -- include processes with no controlling terminal"};

	return (ft_strdup(desc_tab[index]));
}

int					auto_ps(int index, char **name, char **desc)
{
	static char		*flag_tab[27] = {
		"-A", "-C", "-G", "-H", "-L", "-M", "-N", "-O", "-S",
		"-T", "-U", "-Z", "-a", "-c", "-e", "-h", "-j", "-l",
		"-m", "-o", "-p", "-r", "-t", "-u", "-v", "-w", "-x"};

	*name = ft_strdup(flag_tab[index]);
	*desc = auto_get_psdesc(index);
	return (27);
}
