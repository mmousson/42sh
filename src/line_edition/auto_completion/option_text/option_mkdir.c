/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_mkdir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 08:55:49 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/28 08:55:50 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

int			auto_mkdir(int index, char **name, char **desc)
{
	static char	*flag_tab[2] = {"-m", "-p"};
	static char	*desc_tab[2] = {
		"  -- set permission mode",
		"  -- make parent directories as needed"};

	*name = ft_strdup(flag_tab[index]);
	*desc = ft_strdup(desc_tab[index]);
	return (2);
}
