/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 03:42:55 by oboutrol          #+#    #+#             */
/*   Updated: 2019/04/03 17:07:49 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexpars.h"
#include <stdlib.h>
#include "libft.h"

void			ft_ctrld(t_args *args)
{
	if (args && args->str && !args->str[0] && args->line->ctrld)
		ft_exit_clean_args(args, 0);
}

int				ft_quit(t_args *args)
{
	t_history	*tmp;
	t_history	*new;

	if (!args || !args->line || !args->line->isatty)
		return (-1);
	ft_ctrld(args);
	if (args && args->line && args->str && ft_strlen(args->str) > 0)
	{
		tmp = args->line->ry;
		if (!(new = (t_history*)malloc(sizeof(t_history))))
			return (-1);
		new->next = tmp;
		new->prev = NULL;
		if (tmp)
			tmp->prev = new;
		if (!(new->line = ft_strdup(args->str)))
			return (-1);
		args->line->ry = new;
	}
	return (-1);
}
