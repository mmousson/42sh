/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_shell_param.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 14:51:24 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/24 22:11:46 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

#include "libft.h"
static int		expand_one_param(char **str, int j, char ***arge)
{
	char		*expand;
	int			end;

	end = 0;
	if (!(*str))
		return (0);
	if ((*str)[j + 1] == '{')
		ft_putstr("acc\n");
	else
	{
		expand = expand_param((*str) + j, arge, &end);
		if (expand)
		{
			if (insert_word(str, expand, j, end))
				return (1);
		}
	}
	return (0);
}

static int		expand_param_word(char **str, char ***arge)
{
	char		c;
	int			state;
	int			j;

	j = 0;
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
		//ft_putendl(*str);
		if (expand_param_word(str, arge))
			return (1);
		k++;
	}
	return (0);
}
