/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_four_argc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 08:19:20 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/10 16:59:10 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	four_args(char **argv)
{
	if (ft_strequ(argv[1], "!"))
		return (!three_args(++argv));
	else
	{
		ft_putendl_fd("42sh: test: too many arguments",
			STDERR_FILENO);
		return (TEST_FALSE);
	}
}
