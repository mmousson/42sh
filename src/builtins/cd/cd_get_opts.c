/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_get_opts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 21:52:00 by tduval            #+#    #+#             */
/*   Updated: 2019/04/22 21:52:48 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char     get_opts(char **argv, char **dir)
{
	char    res;
	char    cur;
	int		i;
	int		j;

	i = 1;
	res = 0;
	while (argv[i] && argv[i][0] == '-' && argv[i][1] != '\0')
	{
			j = 1;
			cur = res;
			while (argv[i][j])
			{
					if (argv[i][j] == 'L')
							res |= OPT_L;
					else if (argv[i][j] == 'P')
							res |= OPT_P;
					else
					{
							if (argv[i + 1] != NULL)
									return (-1);
							*dir = ft_strdup(argv[i]);
							return (cur);
					}
					j++;
			}
			i++;
	}
	if (argv[i] != NULL && argv[i + 1] != NULL)
			return (-1);
	*dir = ft_strdup(argv[i]);
	return (res);
}

