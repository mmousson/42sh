/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equality_comparison.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 09:19:57 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/16 09:54:41 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	integer_expected(const char *s)
{
	ft_putstr_fd("42sh: test: ", STDERR_FILENO);
	ft_putstr_fd(s, STDERR_FILENO);
	ft_putendl_fd(": integer expression expected", STDERR_FILENO);
	return (TEST_ERROR);
}

int	test_eq(const char *n1, const char *n2)
{
	int	nb1;
	int	nb2;

	if (!ft_string_isdigit(n1))
		return (integer_expected(n1));
	if (!ft_string_isdigit(n2))
		return (integer_expected(n2));
	nb1 = ft_atoi(n1);
	nb2 = ft_atoi(n2);
	return (nb1 == nb2 ? TEST_TRUE : TEST_FALSE);
}

int	test_ne(const char *n1, const char *n2)
{
	int	nb1;
	int	nb2;

	if (!ft_string_isdigit(n1))
		return (integer_expected(n1));
	if (!ft_string_isdigit(n2))
		return (integer_expected(n2));
	nb1 = ft_atoi(n1);
	nb2 = ft_atoi(n2);
	return (nb1 == nb2 ? TEST_FALSE : TEST_TRUE);
}
