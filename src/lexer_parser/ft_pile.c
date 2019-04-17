/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 10:52:54 by oboutrol          #+#    #+#             */
/*   Updated: 2019/04/03 20:27:53 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexpars.h"
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

void		ft_add_pile(int og, t_args *arg)
{
	if (og == 0)
		arg->in = dup(0);
	if (og == 1)
		arg->out = dup(1);
	if (og == 2)
		arg->err = dup(2);
}

void		ft_res_pile(t_args *arg)
{
	if (arg)
	{
		if (arg->in != -1)
		{
			dup2(arg->in, 0);
			close(arg->in);
		}
		if (arg->out != -1)
		{
			dup2(arg->out, 1);
			close(arg->out);
		}
		if (arg->err != -1)
		{
			dup2(arg->err, 2);
			close(arg->err);
		}
	}
}

void		ft_res_red(t_args *arg)
{
	ft_res_pile(arg);
}
