/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_special_params.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 01:13:45 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/30 02:05:37 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "sh42.h"

t_special_vars	g_spec_vars[16] = {
	{0, NULL},
	{1, NULL},
	{2, NULL},
	{3, NULL},
	{4, NULL},
	{5, NULL},
	{6, NULL},
	{7, NULL},
	{8, NULL},
	{9, NULL},
	{10, NULL},
	{11, NULL},
	{12, NULL},
	{13, NULL},
	{14, NULL},
	{15, NULL}
};

int				core_hash_spec_var(char var)
{
	if (var >= 0 && var <= 9)
		return (var - '0');
	else
		return (10 + var % 7);
}

char			*core_spec_var_setget(int id, char *new_value, int set_or_get)
{
	char	*tmp;

	if (set_or_get == SET)
	{
		ft_strdel(&(g_spec_vars[id].value));
		if ((g_spec_vars[id].value = ft_strdup(new_value)) == NULL)
			ft_putendl_fd("Internal Malloc Error", STDERR_FILENO);
		printf("quest = %s\n", g_spec_vars[SPEC_QUESTION].value);
		return (g_spec_vars[id].value);
	}
	else if (set_or_get == GET)
	{
		if ((tmp = ft_strdup(g_spec_vars[id].value)) == NULL)
			ft_putendl_fd("Internal Malloc Error", STDERR_FILENO);
		return (tmp);
	}
	return (NULL);
}
