/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_equality_comparison.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 09:19:57 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/09 18:44:35 by mmousson         ###   ########.fr       */
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
	int			nb1;
	int			nb2;
	const char	*bkp1;
	const char	*bkp2;

	bkp1 = n1;
	bkp2 = n2;
	while (*bkp1 != '\0' && (*bkp1 == '-' || *bkp1 == '+'))
		bkp1++;
	while (*bkp2 != '\0' && (*bkp2 == '-' || *bkp2 == '+'))
		bkp2++;
	if (!ft_string_isdigit(bkp1))
		return (integer_expected(n1));
	if (!ft_string_isdigit(bkp2))
		return (integer_expected(n2));
	nb1 = ft_atoi(n1);
	nb2 = ft_atoi(n2);
	return (nb1 == nb2 ? TEST_TRUE : TEST_FALSE);
}

int	test_ne(const char *n1, const char *n2)
{
	int			nb1;
	int			nb2;
	const char	*bkp1;
	const char	*bkp2;

	bkp1 = n1;
	bkp2 = n2;
	while (*bkp1 != '\0' && (*bkp1 == '-' || *bkp1 == '+'))
		bkp1++;
	while (*bkp2 != '\0' && (*bkp2 == '-' || *bkp2 == '+'))
		bkp2++;
	if (!ft_string_isdigit(bkp1))
		return (integer_expected(n1));
	if (!ft_string_isdigit(bkp2))
		return (integer_expected(n2));
	nb1 = ft_atoi(n1);
	nb2 = ft_atoi(n2);
	return (nb1 == nb2 ? TEST_FALSE : TEST_TRUE);
}
