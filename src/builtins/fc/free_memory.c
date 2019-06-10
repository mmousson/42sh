/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 12:27:27 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/10 16:53:36 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fc.h"

/*
**	Function specific to the 'fc' builtin utility shall free all memory
**	allocated to hold informations about passed options, arguments, and default
**	operands
**
**	Arguments:
**	inf -> A pointer to the Data-Structure holding all infos about the
**		current 'fc' instance
**
**	Return Value: NONE
*/

void	blt_fc_free_memory(t_options_infos *inf)
{
	ft_strdel(&inf->editor_name);
	ft_strdel(&inf->first);
	ft_strdel(&inf->last);
	if (inf->dash_s)
	{
		ft_strdel(&inf->dash_s->old);
		ft_strdel(&inf->dash_s->new);
		ft_memdel((void **)&(inf->dash_s));
	}
	ft_memdel((void **)&(inf));
}
