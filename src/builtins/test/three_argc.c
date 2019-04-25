/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   three_argc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 08:19:22 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/16 10:47:38 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

/*
**
*/

int	three_args(char **argv)
{
	int	i;

	if (ft_strequ(argv[1], "!"))
		return (!two_args(++argv));
	else
	{
		i = -1;
		while (++i < BINARY_TABLE_LEN)
		{
			if (ft_strequ(argv[2], g_binary_table[i].binary_name))
				return (g_binary_table[i].handler(argv[1], argv[3]));
		}
		ft_putstr_fd("42sh: test: ", STDERR_FILENO);
		ft_putstr_fd(argv[2], STDERR_FILENO);
		ft_putendl_fd(": binary operator expected", STDERR_FILENO);
		return (TEST_ERROR);
	}
}
