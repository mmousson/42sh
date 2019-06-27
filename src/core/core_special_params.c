/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_special_params.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 01:13:45 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/27 17:42:39 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh42.h"

/*
**	The table holding the shell's Special Variables
**	Since this table is not declared as global, the only way to interact
**	with it is through the 'core_spec_var_setget' function defined below
*/

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

/*
**	Function to free the shell's reserved vars
**
**	Arguments: NONE
**
**	Return Value: NONE
*/

void	core_free_shell_spec_vars_list(void)
{
	int				i;

	i = -1;
	while (++i < 16)
		ft_strdel(&(g_spec_vars[i].value));
}

/*
**	Functions that returns the index of the Special Variables table defined
**	above, based on the character passed as argument
**
**	Arguments:
**	var -> The character to search the corresponding index of
**
**	Return Value:
**	-1 -> Invalid special var name
**	0 <= x <= 15 -> The corresponding index in the Special Variables table
*/

int		core_hash_spec_var(char var)
{
	if ((var >= '0' && var <= '9') || var == '?' || var == '$' || var == '_'
		|| var == '!')
	{
		if (var >= 0 && var <= 9)
			return (var - '0');
		else
			return (10 + var % 7);
	}
	else
		return (-1);
}

/*
**	This functions serves as a gate between the user and the
**	Shell's Special Variables
**	The 'id' argument identifies which Special Variable the user is interacting
**	with
**	The second argument holds the new value in case the Shell
**	needs to update it
**	The third argument 'set_or_get' tells the function wheter it should update
**	a variable or simply return its value
**
**	Arguments:
**	id -> Integer identifier of the Special Variable the Shell is
**		interacting with
**	new_value -> In case the variable is to be updated, this argument holds
**		the new value (NOTE: the argument is duplicated in memory)
**	set_or_get -> Flag (can be either SET ot GET) telling the function whether
**		it should modify the Special Variable or only return its value
*/

char	*core_spec_var_setget(int id, char *new_value, int set_or_get)
{
	char	*tmp;

	if (set_or_get == SET)
	{
		ft_strdel(&(g_spec_vars[id].value));
		if ((g_spec_vars[id].value = ft_strdup(new_value)) == NULL)
			ft_putendl_fd("42sh: Internal Malloc Error", STDERR_FILENO);
		return (g_spec_vars[id].value);
	}
	else if (set_or_get == GET)
	{
		if ((tmp = ft_strdup(g_spec_vars[id].value)) == NULL)
		{
			if (g_spec_vars[id].value != NULL)
				ft_putendl_fd("42sh: Internal Malloc Error", STDERR_FILENO);
		}
		return (tmp);
	}
	return (NULL);
}
