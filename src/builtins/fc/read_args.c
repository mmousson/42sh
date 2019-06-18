/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 09:42:57 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/18 14:53:14 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fc.h"

static void	split_old_new(t_options_infos *inf, char *arg)
{
	size_t	old_len;
	size_t	new_len;
	char	*catch;

	catch = ft_strchr(arg, '=');
	if ((inf->dash_s->old = ft_strsub(arg, 0, catch - arg)) == NULL)
	{
		ft_putendl_fd("42sh: Internal Malloc Error", STDERR_FILENO);
		return ;
	}
	old_len = ft_strlen(inf->dash_s->old) + 1;
	new_len = ft_strlen(arg) - old_len;
	if ((inf->dash_s->new = ft_strsub(arg, old_len, new_len)) == NULL)
	{
		ft_strdel(&inf->dash_s->old);
		ft_putendl_fd("42sh: Internal Malloc Error", STDERR_FILENO);
		return ;
	}
}

void		blt_fc_read_args(int argc, char **argv, t_options_infos *inf)
{
	int	i;

	i = -1;
	while (++i < argc)
	{
		if (inf->dash_s != NULL && inf->dash_s->old == NULL
			&& ft_strchr(argv[i], '='))
			split_old_new(inf, argv[i]);
		else if (inf->first == NULL)
			inf->first = ft_strdup(argv[i]);
		else if (inf->last == NULL)
		{
			if (ft_valid_to_atoi(argv[i]) && ft_atoi(argv[i]) == 0)
				inf->last = ft_strdup("-1");
			else
				inf->last = ft_strdup(argv[i]);
		}
		else
			break ;
	}
}
