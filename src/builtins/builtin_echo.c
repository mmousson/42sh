/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 15:24:15 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/07 12:27:08 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		write_error(void)
{
	ft_putendl_fd("42sh: echo: write error: Bad file descriptor",
		STDERR_FILENO);
	return (1);
}

int				blt_echo(int argc, char **args, char ***env)
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
		if (i > n + 1 && write(1, " ", 1) == -1)
			return (write_error());
		if (i >= n + 1 && write(1, args[i], ft_strlen(args[i])) == -1)
			return (write_error());
		i++;
	}
	if (!n && write(1, "\n", 1) == -1)
		return (write_error());
	return (0);
}
