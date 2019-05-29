/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_kill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 08:49:26 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/28 08:49:27 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

int			auto_kill(int index, char **name, char **desc)
{
	static char	*flag_tab[34] = {
		"-l", "-n", "-s", "-ABRT", "-ALRM", "-BUS", "-CHLD", "-CONT",
		"-EMT", "-FPE", "-HUP", "-ILL", "-INFO", "-INT", "-IO", "-KILL",
		"-PIPE", "-PROF", "-QUIT", "-SEGV", "-STOP", "-SYS", "-TERM",
		"-TRAP", "-TSTP", "-TTIN", "-TTOU", "-URG", "-USR1", "-USR2",
		"-VRALRM", "-WINCH", "-XCPU", "-XFSZ"};
	static char	*desc_tab[3] = {
		"  -- list signal names or numbers of specified signals",
		"  -- specify signal number",
		"  -- specify signal name"};

	*name = ft_strdup(flag_tab[index]);
	if (index < 3)
		*desc = ft_strdup(desc_tab[index]);
	else
		*desc = ft_strdup(" ");
	return (34);
}
