/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select_pars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 14:43:44 by oboutrol          #+#    #+#             */
/*   Updated: 2019/04/09 15:50:37 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "pars.h"
#define NB_PARS 3

t_tree				*ft_select_pars(t_tok *tok, int start, int end, char c)
{
	static t_tree	*(*fct_pars[NB_PARS])(t_tok*, int, int) = {
		ft_pars_line, ft_pars_cmd, ft_pars_pipe};
	static char		pars_char[NB_PARS] = ";| ";
	int				select;

	select = 0;
	while (select < NB_PARS)
	{
		if (c == pars_char[select])
			return (fct_pars[select])(tok, start, end);
		select++;
	}
	return (NULL);
}
