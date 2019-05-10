/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleans_spa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 15:54:16 by oboutrol          #+#    #+#             */
/*   Updated: 2019/04/10 19:29:48 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"

void		ft_cleans_spa(int *start, int *end, t_tok *token)
{
	int		pos;
	t_tok	*tmp;

	tmp = token;
	pos = 0;
	while (pos < *start && tmp)
	{
		pos++;
		tmp = tmp->next;
	}
	if (tmp && tmp->status == SPA)
		(*start)++;
	while ((pos < *end || *end == -2) && tmp && tmp->next)
	{
		pos++;
		tmp = tmp->next;
	}
	if (tmp && tmp->status == SPA)
	{
		if (*end > -1)
			(*end)--;
		else
			*end = pos - 1;
	}
}
