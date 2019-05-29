/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tild.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 19:07:52 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/29 19:33:05 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int			expand_tilde(char **str)
{
	int		state;
	int		j;
	char	c;

	j = 0;
	state = 0;
	while (str && *str && (c = (*str)[j]))
	{
		if (state % 2 == 1)
			state--;
		else if (c == '\\')
			state++;
		else if (c == '~' && !state)
		{
			//if (expand_tild_unit(str, &j))
			;//	return (1);
		}
		else if (c == '\'')
			state = -state + 2;
		j++;
	}
	return (0);
}
