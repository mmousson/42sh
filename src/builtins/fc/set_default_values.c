/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_default_values.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:13:15 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/04 10:13:15 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fc.h"

/*
**
*/

void	blt_fc_set_default_values(t_options_infos *inf)
{
	if (inf->dash_s != NULL)
	{
		if (inf->first == NULL)
			inf->first = ft_strdup("-1");
	}
	else
	{
		if (inf->first == NULL)
		{
			inf->first = ft_strdup("-16");
			inf->last = ft_strdup("-1");
		}
		else if (inf->last == NULL)
		{
			if (inf->listing)
				inf->last = ft_strdup("-1");
			else
				inf->last = ft_strdup(inf->first);
		}
	}
}
