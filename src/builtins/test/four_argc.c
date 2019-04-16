/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   four_argc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 08:19:20 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/16 09:10:45 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

/*
**
*/

int	four_args(int argc, char **argv)
{
	if (ft_strequ(argv[1], "!"))
		return (!three_args(4, ++argv));
	else
	{
		ft_putendl_fd("42sh: test: Syntax results in undefined behaviour",
			STDERR_FILENO);
		return (TEST_FALSE);
	}
}
