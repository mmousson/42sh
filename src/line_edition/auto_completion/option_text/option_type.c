/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 08:59:44 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/28 08:59:45 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

int			auto_type(int index, char **name, char **desc)
{
	static char	*flag_tab[1] = {
		"-a"};
	static char	*desc_tab[1] = {
		"  -- print all occurrences in path"};

	*name = ft_strdup(flag_tab[index]);
	*desc = ft_strdup(desc_tab[index]);
	return (1);
}
