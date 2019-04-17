/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 04:28:54 by oboutrol          #+#    #+#             */
/*   Updated: 2019/03/19 02:43:51 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexpars.h"
#include "libft.h"
#include <stdlib.h>

int			nothing(t_args *args)
{
	(void)args;
	return (0);
}

char		*ft_new_word(char k)
{
	char	*str;

	if (!(str = (char*)malloc(sizeof(char) * 2)))
		return (NULL);
	str[0] = k;
	str[1] = '\0';
	return (str);
}

t_word		*ft_brand_new_word(char k, int stat)
{
	t_word	*new;

	if (!(new = init_word()))
		return (NULL);
	new->value = ft_new_word(k);
	if (stat > 1)
		new->type = stat;
	return (new);
}

int			ft_add_word(t_cmd *cmd, char k)
{
	t_word	*tmp;
	t_word	*target;

	target = ft_target(cmd);
	tmp = target;
	if (!target)
		if ((target = init_word()) == NULL)
			return (1);
	while (target->next)
		target = target->next;
	if (target->value == NULL)
	{
		if (!(target->value = ft_new_word(k)))
			return (1);
		if (cmd->status > 1)
			target->type = cmd->status;
	}
	else if ((target->next = ft_brand_new_word(k, cmd->status)) == NULL)
		return (1);
	target = tmp;
	return (0);
}

int			ft_newarg(t_args *args)
{
	t_cmd	*tmp_c;

	tmp_c = args->cmd;
	while (args->cmd && args->cmd->next)
		args->cmd = args->cmd->next;
	if (args->cmd && args->str)
		if (ft_add_word(args->cmd, args->str[args->k]))
			return (1);
	args->cmd = tmp_c;
	return (0);
}
