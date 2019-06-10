/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_param_glob.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 23:16:31 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/09 21:06:27 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include <stdlib.h>
#include "sh42.h"
#include "libft.h"

void		expand_size_word(char **value, const char *str, char ***arge)
{
	char	*var;
	char	*expanded;
	int		size;

	expanded = NULL;
	if ((var = take_word_expand(str + 1, arge)))
	{
		expanded = utility_get_param(var, *arge);
		ft_strdel(&var);
	}
	size = 0;
	while (expanded && expanded[size])
		size++;
	*value = ft_itoa(size);
	ft_strdel(&expanded);
}

void		expand_glo(char **value, const char *str, char *var, char ***arge)
{
	int		greedy;
	int		suffix;
	char	*pattern;
	char	*var_exp;

	suffix = str[0] == '%' ? 1 : 0;
	if (str[1] == str[0])
	{
		greedy = 1;
		pattern = take_word_expand(str + 2, arge);
	}
	else
	{
		greedy = 0;
		pattern = take_word_expand(str + 1, arge);
	}
	var_exp = utility_get_param(var, *arge);
	*value = remove_substring(var_exp, pattern, suffix, greedy);
}
