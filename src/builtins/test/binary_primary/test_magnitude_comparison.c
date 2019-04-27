/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magnitude_comparison.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 09:41:33 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/16 09:55:01 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

/*
**
*/

int	test_gt(const char *n1, const char *n2)
{
	int	nb1;
	int	nb2;

	if (!ft_string_isdigit(n1))
		return (integer_expected(n1));
	if (!ft_string_isdigit(n2))
		return (integer_expected(n2));
	nb1 = ft_atoi(n1);
	nb2 = ft_atoi(n2);
	return (nb1 > nb2 ? TEST_TRUE : TEST_FALSE);
}

/*
**
*/

int	test_ge(const char *n1, const char *n2)
{
	int	nb1;
	int	nb2;

	if (!ft_string_isdigit(n1))
		return (integer_expected(n1));
	if (!ft_string_isdigit(n2))
		return (integer_expected(n2));
	nb1 = ft_atoi(n1);
	nb2 = ft_atoi(n2);
	return (nb1 >= nb2 ? TEST_TRUE : TEST_FALSE);
}

/*
**
*/

int	test_lt(const char *n1, const char *n2)
{
	int	nb1;
	int	nb2;

	if (!ft_string_isdigit(n1))
		return (integer_expected(n1));
	if (!ft_string_isdigit(n2))
		return (integer_expected(n2));
	nb1 = ft_atoi(n1);
	nb2 = ft_atoi(n2);
	return (nb1 < nb2 ? TEST_TRUE : TEST_FALSE);
}

/*
**
*/

int	test_le(const char *n1, const char *n2)
{
	int	nb1;
	int	nb2;

	if (!ft_string_isdigit(n1))
		return (integer_expected(n1));
	if (!ft_string_isdigit(n2))
		return (integer_expected(n2));
	nb1 = ft_atoi(n1);
	nb2 = ft_atoi(n2);
	return (nb1 <= nb2 ? TEST_TRUE : TEST_FALSE);
}
