/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_param_glob.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 23:16:31 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/04 21:30:45 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include <stdlib.h>
#include "sh42.h"

#include "libft.h"
void		expand_glo(char **value, const char *str, char *var, char ***arge)
{
	int		greedy;
	int		suffix;
	char	*pattern;
	char	*var_exp;

	suffix = str[0] == '%' ? 1 : 0;
	if (str[0] == '%')
		ft_putstr("type: %, ");
	else
		ft_putstr("type: #, ");
	if (str[1] == str[0])
	{
		greedy = 1;
		ft_putstr("searching greedy occurence of: ");
		pattern = take_word_expand(str + 2, arge);
	}
	else
	{
		greedy = 0;
		ft_putstr("searching lazy occurence of: `");
		pattern = take_word_expand(str + 1, arge);
	}
	ft_putstr(pattern);
	ft_putstr("'\nin variable: ");
	ft_putstr(var);
	ft_putstr(", expanded as: `");
	var_exp = utility_get_param(var, *arge);
	ft_putstr(var_exp);
	ft_putstr("'\n\n");
	*value = remove_substring(var_exp, pattern, suffix, greedy);
	ft_putstr("after match\n");
}
