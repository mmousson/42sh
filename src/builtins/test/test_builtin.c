/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 09:23:25 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/16 12:17:16 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

/*
**
*/

t_unary_matcher		g_unary_table[UNARY_TABLE_LEN] = {
	{"-b", &check_type, S_IFBLK},
	{"-c", &check_type, S_IFCHR},
	{"-d", &check_type, S_IFDIR},
	{"-e", &check_type, IGNORE_TYPE},
	{"-f", &check_type, S_IFREG},
	{"-g", &check_type, S_ISGID},
	{"-L", &check_type, S_IFLNK},
	{"-n", &test_n, IGNORE_TYPE},
	{"-p", &check_type, S_IFIFO},
	{"-r", &check_type, R_OK},
	{"-S", &check_type, S_IFSOCK},
	{"-s", &check_type, CHECK_SIZE},
	{"-u", &check_type, S_ISUID},
	{"-w", &check_type, W_OK},
	{"-x", &check_type, X_OK},
	{"-z", &test_z, IGNORE_TYPE}
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
