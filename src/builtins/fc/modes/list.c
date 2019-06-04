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

/*
**	This function simply lists commands available in the history
**	All commands between 'inf->from' to 'inf->to' (inclusive) are displayed
**
**	Arguments:
**	inf -> A pointer to the Data-Structure holding all informations about
**		the current 'fc' utility instance
**
**	Return Value: Always 0
**		Because we are displaying commands and not executing them, therefore
**		no failure can occur
*/

int	blt_fc_list(t_options_infos *inf)
{
	t_history	*current;
	t_history	*target;

	current = inf->from;
	target = inf->to;
	while (current != NULL)
	{
		if (!inf->suppressed)
			ft_putnbr(current->id);	
		ft_putchar('\t');
		ft_putendl(current->line);
		if (current == target)
			break ;
		if (inf->reversed)
			current = current->next;
		else
			current = current->prev;
	}
	return (0);
}
