/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_get_opts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 21:52:00 by tduval            #+#    #+#             */
/*   Updated: 2019/05/06 01:39:54 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"
#include "libft.h"

/*
**	Basically the parser of the cd builtin.
**	It will first take the options, then once it encouters takes the next
**	arg as the directory variable. If there is any argument after the
**	directory one, then it is considered as an error.
*/

static char	check_arg(char *arg, char *next, char **dir, char cur)
{
	char	res;
	int		i;

	res = 0;
	i = 1;
	while (arg[i])
	{
		if (arg[i] == 'L')
			res = OPT_L;
		else if (arg[i] == 'P')
			res = OPT_P;
		else
		{
			if (next != NULL)
				return (-1);
			*dir = ft_strdup(arg);
			return (cur);
		}
		i++;
	}
	return (res);
}

char		cd_get_opts(char **argv, char **dir)
{
	char	res;
	char	cur;
	int		i;

	i = 1;
	res = 0;
	while (argv[i] && argv[i][0] == '-'
			&& argv[i][1] != '\0'
			&& ft_strcmp(argv[i], "--"))
	{
		cur = res;
		if ((res = check_arg(argv[i], argv[i + 1], dir, cur)) == -1)
			return (-1);
		i++;
	}
	if (ft_strequ(argv[i], "--"))
		i++;
	if (argv[i] != NULL && argv[i + 1] != NULL)
		return (-1);
	*dir = argv[i];
	return (res);
}
