/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_spec_param.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 16:06:51 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/09 21:09:39 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <stdlib.h>
#define OFFSET 10

char			*get_spec_param(const char *word)
{
	static char	*table = "?$_!";
	char		spec;
	int			k;

	if (!word || !word[0])
		return (NULL);
	spec = word[0];
	if (spec >= '0' && spec <= '9')
		return (core_spec_var_setget(spec - '0', NULL, GET));
	k = -1;
	while (table[++k])
		if (spec == table[k])
			return (core_spec_var_setget(k + OFFSET, NULL, GET));
	return (NULL);
}
