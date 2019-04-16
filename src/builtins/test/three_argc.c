/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   three_argc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 08:19:22 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/16 09:05:39 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

/*
**
*/

int	three_args(int argc, char **argv)
{
	int	i;

	if (ft_strequ(argv[1], "!"))
		return (!two_args(3, ++argv));
	else
	{
		i = -1;
		if (ft_strequ(argv[2], g_binary_table[i].binary_name))
			return (g_binary_table[i].handler(argv[1], argv[3]));
		ft_putendl_fd("42sh: test: Syntax results in undefined behaviour",
			STDERR_FILENO);
		return (TEST_FALSE);
	}
}
