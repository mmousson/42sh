/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 08:59:23 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/28 09:33:58 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

static char			*auto_get_testdesc_next(int index)
{
	static char		*desc_tab[8] = {
		"  -- true if the integers n1 and n2 are algebraically equal",
		"  -- true if the integers n1 and n2 are not algebraically equal",
		"  -- true if n1 is algebraically greater than or equal to n2",
		"  -- true if the integer n1 is algebraically less than the integer n2",
		"  -- true if n1 is algebraically less than or equal to n2",
		"  -- true if the strings s1 and s2 are identical",
		"  -- true if the strings s1 and s2 are not identical",
		"  -- true if expression is false"};

	return (ft_strdup(desc_tab[index]));
}

static char			*auto_get_testdesc(int index)
{
	static char		*desc_tab[15] = {
		"  -- true if file exists and is a block special file",
		"  -- true if file exists and is a character special file",
		"  -- true if file exists and is a directory",
		"  -- true if file exists (regardless of type)",
		"  -- true if file exists and is a regular file",
		"  -- true if file exists and its set group ID flag is set",
		"  -- true if file exists and is a symbolic link",
		"  -- true if file is a named pipe (FIFO)",
		"  -- true if file exists and is readable",
		"  -- true if file exists and is a socket",
		"  -- true if file exists and has a size greater than zero",
		"  -- true if file exists and its set user ID flag is set",
		"  -- true if file exists and is writable",
		"  -- true if file exists and is executable",
		"  -- true if the length of string is zero"};

	if (index > 14)
		return (auto_get_testdesc_next(index - 15));
	return (ft_strdup(desc_tab[index]));
}

int					auto_test(int index, char **name, char **desc)
{
	static char		*flag_tab[23] = {
		"-b", "-c", "-d", "-e", "-f", "-g", "-L", "-p", "-r",
		"-S", "-s", "-u", "-w", "-x", "-z", "-eq", "-ne", "-ge",
		"-lt", "-le", " =", " !=", " !"};

	*name = ft_strdup(flag_tab[index]);
	*desc = auto_get_testdesc(index);
	return (23);
}
