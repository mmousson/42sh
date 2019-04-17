/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 16:36:43 by oboutrol          #+#    #+#             */
/*   Updated: 2019/03/30 06:25:02 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexpars.h"
#include "libft.h"

int			ft_redirect(t_args *args)
{
	t_cmd	*tmp;

	tmp = args->cmd;
	while (args->cmd && args->cmd->next)
		args->cmd = args->cmd->next;
	if (args->cmd)
		args->cmd->status = args->old_status;
	if (args->agg)
		args->cmd->status += 10 * args->agg;
	args->agg = 0;
	args->cmd = tmp;
	return (0);
}

int			ft_newred(t_args *args)
{
	ft_redirect(args);
	return (ft_newarg(args));
}
