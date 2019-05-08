/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 15:02:59 by oboutrol          #+#    #+#             */
/*   Updated: 2019/04/30 20:04:30 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"
#include <stdlib.h>

t_tree		*ft_pars_cmd(t_tok *token, int start, int end)
{
	t_tok	*tok;
	t_tree	*tree;

	ft_cleans_spa(&start, &end, token);
	tok = ft_go_start(token, start);
	if (tok == NULL || (end != -2 && end < start))
		return (NULL);
	if ((tree = ft_sep(token, start, end, '|')))
		return (tree);
	else if ((tree = ft_pars_pipe(token, start, end)))
		return (tree);
	return (NULL);
}
