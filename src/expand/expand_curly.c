/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_curly.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 09:18:57 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/25 11:27:21 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"
#include "expand.h"
#include "libft.h"

char		*expand_curly(const char *str, char ***arge, int *end, int *error)
{
	int		k;
	int		end_var;
	char	*var;
	char	*value;

	end_var = 0;
	k = 0;
	while (str[k] != '}' && str[k])
	{
		if (!end_var && !is_char_exp(str[k]))
			end_var = k;
		k++;
	}
	if (!end_var)
		end_var = k;
	*end = k + 1;
	if (str[k])
		(*end)++;
	if (end_var != k)//to adapt with :- :+ ##
	{
		*error = -1;
		return (NULL);
	}
	var = ft_strsub(str, 0, end_var);
	value = ft_getenv(*arge, var);
	ft_strdel(&var);
	return (value);
}
