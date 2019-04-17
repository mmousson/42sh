/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_empargs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 02:37:47 by oboutrol          #+#    #+#             */
/*   Updated: 2019/03/17 21:11:19 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexpars.h"
#include <stdlib.h>

int			ft_emp_word(t_cmd *cmd)
{
	t_word	*tmp;
	t_word	*target;

	target = ft_target(cmd);
	tmp = target;
	if (target)
	{
		while (target->next)
			target = target->next;
		if (target->value)
			target->news = 1;
	}
	target = tmp;
	return (0);
}

int			ft_empargs(t_args *args)
{
	t_cmd	*tmp_c;

	tmp_c = args->cmd;
	while (args->cmd && args->cmd->next)
		args->cmd = args->cmd->next;
	if (args->cmd && args->str)
		if (ft_emp_word(args->cmd))
			return (1);
	args->cmd = tmp_c;
	return (0);
}
