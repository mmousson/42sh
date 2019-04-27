/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 15:24:15 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/26 15:24:58 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				echo(int argc, char **args, char ***env)
{
	int			i;
	int			n;

	n = 0;
	(void)argc;
	(void)env;
	if (!args || !args[0])
		return (0);
	if (args[1] && !ft_strcmp(args[1], "-n"))
		n = 1;
	i = n + 1;
	while (args[i])
	{
		if (i > n + 1)
			ft_putchar(' ');
		if (i >= n + 1)
			ft_putstr(args[i]);
		i++;
	}
	if (!n)
		ft_putchar('\n');
	return (1);
}
