/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 17:56:57 by oboutrol          #+#    #+#             */
/*   Updated: 2019/04/25 10:50:37 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lex.h"
#include "libft.h"

int				get_prompt(int stat)
{
	static int	tab_stat[3] = {
		DQ, SQ, BS};
	static int	tab_prmt[3] = {
		PDQUOTE, PQUOTE, PBACKS};
	int			k;

	k = 0;
	while (k < 3)
	{
		if (stat == tab_stat[k])
			return (tab_prmt[k]);
		k++;
	}
	return (PDEF);
}

void			ft_more(t_stat *stat, char **str)
{
	char		*fus;
	char		*tmp;
	int			prompt;
	
	prompt = get_prompt(stat->old_status);
	fus = NULL;
	while (!fus)
	{
		fus = ft_get_line(prompt, NULL);
		if (!(tmp = ft_strjoin(*str, fus)))
			return ;
		free(*str);
		*str = tmp;
	}
	if (fus)
	{
		free(fus);
		fus = NULL;
	}
	stat->k--;
	stat->status = stat->old_status;
}
