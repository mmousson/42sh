/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 09:23:25 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/16 10:10:52 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

/*
**
*/

t_unary_matcher		g_unary_table[UNARY_TABLE_LEN] = {
	{"-b", NULL},
	{"-c", NULL},
	{"-d", NULL},
	{"-e", NULL},
	{"-f", NULL},
	{"-g", NULL},
	{"-L", NULL},
	{"-p", NULL},
	{"-r", NULL},
	{"-S", NULL},
	{"-s", NULL},
	{"-u", NULL},
	{"-w", NULL},
	{"-x", NULL},
	{"-z", NULL}
};

/*
**
*/

t_binary_matcher	g_binary_table[BINARY_TABLE_LEN] = {
	{"=", &ft_strcmp},
	{"!=", &ft_strequ},
	{"-eq", &test_eq},
	{"-ne", &test_ne},
	{"-gt", &test_gt},
	{"-ge", &test_ge},
	{"-lt", &test_lt},
	{"-le", &test_le}
};

/*
**
*/

int					ft_test(int argc, char **argv, char ***env)
{
	(void)env;
	if (argc == 1)
		return (TEST_FALSE);
	else if (argc == 2)
	{
		if (ft_strlen(argv[1]) != 0)
			return (TEST_TRUE);
		else
			return (TEST_FALSE);
	}
	else if (argc == 3)
		return (two_args(argv));
	else if (argc == 4)
		return (three_args(argv));
	else if (argc == 5)
		return (four_args(argv));
	else
	{
		ft_putendl_fd("42sh: test: too many arguments", STDERR_FILENO);
		return (TEST_ERROR);
	}
}
