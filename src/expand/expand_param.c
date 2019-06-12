/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_param.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 14:27:00 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/12 04:17:51 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "exe.h"
#include "sh42.h"
#include "expand.h"
#include "libft.h"
#include <stdlib.h>

int			is_char_exp(char c)
{
	if (!c)
		return (0);
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

char		*expand_param(const char *str, char ***arge, int *end)
{
	char	*value;
	char	*word;
	int		k;

	if (!str || str[0] != '$')
		return (NULL);
	k = 1;
	while (is_char_exp(str[k]) && (!ft_isdigit(str[1])))
		k++;
	word = ft_strsub(str, 1, k - 1);
	if (!(value = get_spec_param(&(str[1]))))
		value = utility_get_param(word, *arge);
	ft_strdel(&word);
	*end = k - 1;
	if (ft_strchr("?$!", str[1]) || ft_isdigit(str[1]))
		(*end)++;
	return (value);
}
