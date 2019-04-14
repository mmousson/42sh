/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_alias_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 06:12:09 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/14 08:52:44 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh42.h"

/*
**	Nothing to say here
**
**	Arguments: NONE
**
**	Return Value: NONE
*/

void	free_alias_list(void)
{
	t_alias	*next;

	while (alias_list)
	{
		ft_strdel(&(alias_list->token));
		ft_strdel(&(alias_list->replacement));
		next = alias_list->next;
		ft_memdel((void **)&(alias_list));
		alias_list = next;
	}
}
