/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_date.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 08:48:33 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/28 08:48:34 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

int			auto_date(int index, char **name, char **desc)
{
	static char	*flag_tab[7] = {
		"-f", "-j", "-n", "-r", "-u", "-v", "-d"};
	static char	*desc_tab[7] = {
		"  -- use specified format for input",
		"  -- do not try to set date",
		"  -- only set time on current machine",
		"  -- output date specified by reference time",
		"  -- display or set time in UTC",
		"  -- adjust and print (but not set) date",
		"  -t"};

	*name = ft_strdup(flag_tab[index]);
	*desc = ft_strdup(desc_tab[index]);
	return (7);
}
