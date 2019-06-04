/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:26:00 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/04 17:26:00 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fc.h"

int	blt_fc_list(t_options_infos *inf)
{
	t_history	*current;
	t_history	*target;
	
	target = inf->reversed ? inf->to : inf->from;
	current = inf->reversed ? inf->from : inf->to;
	while (current != NULL)
	{
		ft_putchar('\t');
		ft_putendl(current->line);
		if (current == target)
			break ;
		current = current->prev;
	}
	return (0);
}
