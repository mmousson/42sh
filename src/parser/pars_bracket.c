/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_bracket.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 11:41:42 by oboutrol          #+#    #+#             */
/*   Updated: 2019/07/01 12:18:17 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int			pars_bracket(t_tok **tok)
{
	char	*line;
	int		k;
	char	end;

	k = 0;
	if (!(*tok))
		return (0);
	line = (*tok)->content;
	end = line[0] == '(' ? ')' : 0;
	if (!end)
		end = line[0] == '{' ? '}' : 0;
	while (line[k] && line[k] != end)
	{
		if (!end && (line[k] == '{' || line [k] == '('))
		{
			ft_putstr_fd("42sh: Parse Error\n", 2);
			return (1);
		}
		k++;
	}
	if (line[k] && line[k +1])
	{
		ft_putstr_fd("42sh: Parse Error\n", 2);
		return (1);
	}
	return (0);
}
