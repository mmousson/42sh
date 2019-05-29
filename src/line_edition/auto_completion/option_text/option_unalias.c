/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_unalias.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 08:59:50 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/28 08:59:52 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

int			auto_unalias(int index, char **name, char **desc)
{
	static char	*flag_tab[1] = {"-a"};
	static char	*desc_tab[1] = {
		"  -- remove all alias definitions"};

	*name = ft_strdup(flag_tab[index]);
	*desc = ft_strdup(desc_tab[index]);
	return (1);
}
