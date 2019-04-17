/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 01:08:23 by oboutrol          #+#    #+#             */
/*   Updated: 2019/03/17 23:32:11 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexpars.h"
#include <stdlib.h>

int			ft_pipe(t_args *args)
{
	t_cmd	*tmp;

	tmp = args->cmd;
	while (args->cmd && args->cmd->next)
		args->cmd = args->cmd->next;
	if (args->cmd)
	{
		if (!(args->cmd->next = init_cmd()))
			return (1);
		args->cmd->pipe = 1;
	}
	args->cmd = tmp;
	return (0);
}

int			ft_newcmd(t_args *args)
{
	t_cmd	*tmp;

	tmp = args->cmd;
	while (args->cmd && args->cmd->next)
		args->cmd = args->cmd->next;
	if (args->cmd)
		if (!(args->cmd->next = init_cmd()))
			return (1);
	args->cmd = tmp;
	return (0);
}
