/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_two_argc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 08:19:25 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/10 16:59:24 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	two_args(char **a)
{
	int	i;

	if (ft_strequ(a[1], "!"))
		return (ft_strlen(a[2]) == 0 ? TEST_TRUE : TEST_FALSE);
	else
	{
		i = -1;
		while (++i < UNARY_TABLE_LEN)
		{
			if (ft_strequ(a[1], g_unary_table[i].unary_name))
				return (g_unary_table[i].handler(a[2], g_unary_table[i].mask));
		}
		ft_putstr_fd("42sh: test: ", STDERR_FILENO);
		ft_putstr_fd(a[1], STDERR_FILENO);
		ft_putendl_fd(": unary operator expected", STDERR_FILENO);
		return (TEST_ERROR);
	}
}
