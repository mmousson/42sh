/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_jobs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 08:49:22 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/28 08:49:23 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

int			auto_jobs(int index, char **name, char **desc)
{
	static char	*flag_tab[2] = {"-l", "-p"};
	static char	*desc_tab[2] = {
		"  -- list process IDs",
		"  -- list process groups"};

	*name = ft_strdup(flag_tab[index]);
	*desc = ft_strdup(desc_tab[index]);
	return (2);
}
