/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_rer_lr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 18:11:25 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/08 14:13:15 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"
#include <stdlib.h>

t_tree		*ft_pars_rer_rig(t_tok *token, int start, int end)
{
	t_tok	*tok;

	tok = ft_go_start(token, start);
	(void)tok;
	if (end != -2 && start > end)
		return (NULL);
	return (NULL);
}

t_tree		*ft_pars_rer_lef(t_tok *token, int start, int end)
{
	t_tok	*tok;
	
	tok = ft_go_start(token, start);
	(void)tok;
	if (end != -2 && start > end)
		return (NULL);
	return (NULL);
}
