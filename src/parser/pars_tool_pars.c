/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_pars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 20:06:34 by oboutrol          #+#    #+#             */
/*   Updated: 2019/04/10 16:55:28 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"
#include <stdlib.h>

t_tok		*ft_go_status(t_tok *token, int *pos, int status, int end)
{
	t_tok	*tmp;

	tmp = token;
	while (tmp && tmp->status != status && (end == -2 || *pos < end))
	{
		tmp = tmp->next;
		(*pos)++;
	}
	return (tmp);
}

t_tok		*ft_go_start(t_tok *token, int start)
{
	t_tok	*tok;

	tok = token;
	while (tok && start)
	{
		tok = tok->next;
		start--;
	}
	if (start != 0)
		return (NULL);
	return (tok);
}
