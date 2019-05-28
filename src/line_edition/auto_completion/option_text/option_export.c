/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 08:49:00 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/28 08:49:07 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

int			auto_export(int index, char **name, char **desc)
{
	static char	*flag_tab[1] = {"-p"};
	static char	*desc_tab[1] = {
		"  -- write to the standard output the names and values"};

	*name = ft_strdup(flag_tab[index]);
	*desc = ft_strdup(desc_tab[index]);
	return (1);
}
