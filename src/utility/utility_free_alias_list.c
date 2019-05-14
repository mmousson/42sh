/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_free_alias_list.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 06:12:09 by mmousson          #+#    #+#             */
/*   Updated: 2019/05/14 04:51:52 by mmousson         ###   ########.fr       */
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

	while (g_alias_list)
	{
		ft_strdel(&(g_alias_list->token));
		ft_strdel(&(g_alias_list->replacement));
		next = g_alias_list->next;
		ft_memdel((void **)&(g_alias_list));
		g_alias_list = next;
	}
}
