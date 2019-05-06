/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_tool.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 08:42:08 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/01 09:00:04 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char			**extend(char **argv, char *str)
{
	char		**tabl;
	int			size;

	size = 0;
	if (argv)
		while (argv[size])
			(size)++;
	if (!(tabl = (char**)malloc(sizeof(char*) * (size + 2))))
		return (NULL);
	tabl[size + 1] = 0;
	tabl[size] = str;
	while (--size >= 0)
		tabl[size] = argv[size];
	return (tabl);
}
