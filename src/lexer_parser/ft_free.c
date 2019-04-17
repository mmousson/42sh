/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 08:16:57 by oboutrol          #+#    #+#             */
/*   Updated: 2019/04/04 14:05:00 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexpars.h"
#include <stdlib.h>

void	ft_exit_clean_args(t_args *args, int ret)
{
	if (args)
		ft_free_arg(args);
	if (args->arge)
	{
		ft_del_words_tables(args->arge);
		args->arge = NULL;
	}
	if (args->line)
		ft_quiterm(args->line);
	exit(ret);
}

void	ft_free_words_tables(char **tabl)
{
	int	k;

	if (tabl)
	{
		k = 0;
		while (tabl[k])
		{
			free(tabl[k]);
			k++;
		}
		free(tabl);
	}
}
