/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lim.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 00:26:48 by oboutrol          #+#    #+#             */
/*   Updated: 2019/04/03 17:21:06 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexpars.h"
#include "libft.h"
#include <stdlib.h>

static void	ft_add_nbr(t_word *old_targ, t_word *target, t_args *args)
{
	int		nbr;

	if ((nbr = ft_atoi(target->value)) > 0)
	{
		if (old_targ)
		{
			args->agg = nbr;
			if (old_targ)
				old_targ->next = NULL;
			ft_free_word(target);
		}
	}
}

static int	ft_add_agg(t_cmd *cmd, t_args *args)
{
	t_word	*tmp;
	t_word	*target;
	t_word	*old_targ;

	old_targ = NULL;
	target = ft_target(cmd);
	tmp = target;
	if (!target)
		return (1);
	while (target->next)
	{
		old_targ = target;
		target = target->next;
	}
	if (target->value == NULL)
		return (1);
	else
		ft_add_nbr(old_targ, target, args);
	target = tmp;
	return (0);
}

int			ft_lim(t_args *args)
{
	t_cmd	*tmp_c;

	tmp_c = args->cmd;
	while (args->cmd && args->cmd->next)
		args->cmd = args->cmd->next;
	if (args->cmd && args->str)
		if (ft_add_agg(args->cmd, args))
			return (1);
	args->cmd = tmp_c;
	ft_empargs(args);
	return (0);
}
