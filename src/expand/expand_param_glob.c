/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_param_glob.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 23:16:31 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/04 02:06:38 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include <stdlib.h>
#include "sh42.h"

#include "libft.h"
void	expand_hash(char **value, const char *str, char *var, char ***arge)
{
	(void)value;
	ft_putstr("type: #, ");
	if (str[1] == '#')
	{
		ft_putstr("searching greedy occurence of: ");
		ft_putstr(take_word_expand(str + 2, arge));
	}
	else
	{
		ft_putstr("searching lazy occurence of: `");
		ft_putstr(take_word_expand(str + 1, arge));
	}
	ft_putstr("'\nin variable: ");
	ft_putstr(var);
	ft_putstr(", expanded as: ");
	ft_putstr(utility_get_param(var, *arge));
	ft_putstr("'\n");
}

void	expand_perc(char **value, const char *str, char *var, char ***arge)
{
	(void)value;
	ft_putstr("type: %, ");
	if (str[1] == '%')
	{
		ft_putstr("searching greedy occurence of: ");
		ft_putstr(take_word_expand(str + 2, arge));
	}
	else
	{
		ft_putstr("searching lazy occurence of: `");
		ft_putstr(take_word_expand(str + 1, arge));
	}
	ft_putstr("'\nin variable: ");
	ft_putstr(var);
	ft_putstr(", expanded as: ");
	ft_putstr(utility_get_param(var, *arge));
	ft_putstr("'\n");
}
