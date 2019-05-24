/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_shell_param.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 14:51:24 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/24 17:32:48 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

#include "libft.h"
static int		expand_one_param(char **str, int j, char ***arge)
{
	char		*expand;
	if (!(*str))
		return (0);
	if ((*str)[j + 1] == '{')
		ft_putstr("acc\n");
	else
	{
		expand = expand_param((*str) + j, arge);
		if (expand)
			ft_putstr(expand);
		ft_putstr("\n");
	}
	return (0);
}

static int		expand_param_word(char **str, char ***arge, int j)
{
	char		c;
	int			state;

	state = 0;
	while ((c = (*str)[j]))
	{
		if (state % 2 == 1)
			state--;
		else if (c == '\\')
			state ++;
		else if (c == '$' && !state)
		{
			if (expand_one_param(str, j, arge))
				return (1);
		}
		else if (c == '\'')
			state = -state + 2;
		j++;
	}
	return (0);
}

int		expand_shell_param(char ***argv, char ***arge)
{
	char		**str;
	int			k;

	if (!argv || !(*argv))
		return (1);
	k = 0;
	while ((str = &((*argv)[k])) && *str)
	{
		if (expand_param_word(str, arge, k))
			return (1);
		k++;
	}
	return (0);
}
