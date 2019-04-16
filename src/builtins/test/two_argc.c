/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   two_argc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 08:19:25 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/16 08:52:06 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

#include <stdio.h>

/*
**
*/

int	two_args(int argc, char **argv)
{
	int	i;

	if (ft_strequ(argv[1], "!"))
		return (ft_strlen(argv[2] == 0) ? TEST_TRUE : TEST_FALSE);
	else
	{
		i = -1;
		while (++i < UNARY_TABLE_LEN)
		{
			if (ft_strequ(argv[1], g_unary_table[i].unary_name))
				return (g_unary_table[i].handler(argv[2]));
		}
		ft_putendl_fd("When passing two arguments to 'test' builtin, the first"
			" argument must be an unary primary, otherwise results are "
			"unspecified", STDERR_FILENO);
		return (TEST_FALSE);
	}
}
