/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 01:51:39 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/18 12:29:41 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unset.h"

/*
**	============================= BUITLIN COMMAND =============================
**	Main function for the 'unset' utility
**	No accepted options
**	The normal behaviour of this utility is to remove all variables whose name
**	are listed in the utility arguments
**	from the shell's internal variables list AND the environment
**
**	Return Value: ALWAYS 0
*/

int	blt_unset(int argc, char **argv, char ***env)
{
	int		i;

	i = 0;
	while (++i < argc)
		utility_delete_var(argv[i], env);
	return (0);
}
