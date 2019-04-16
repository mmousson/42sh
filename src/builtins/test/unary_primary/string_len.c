/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 11:10:42 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/16 11:23:04 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

/*
**
*/

int	test_z(const char *string, int mask)
{
	(void)mask;
	if (ft_strlen(string) == 0)
		return (TEST_TRUE);
	else
		return (TEST_FALSE);
}

/*
**
*/

int	test_n(const char *string, int mask)
{
	(void)mask;
	if (ft_strlen(string) == 0)
		return (TEST_FALSE);
	else
		return (TEST_TRUE);
}
