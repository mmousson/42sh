/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 04:43:26 by oboutrol          #+#    #+#             */
/*   Updated: 2019/04/04 14:04:35 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexpars.h"
#include <stdlib.h>
#include "libft.h"

void		ft_free_word(t_word *word)
{
	if (word)
	{
		ft_free_word(word->next);
		if (word->value)
		{
			free(word->value);
			word->value = NULL;
		}
		free(word);
		word = NULL;
	}
}

void		ft_free_cmd(t_cmd *cmd)
{
	if (cmd)
	{
		ft_free_cmd(cmd->next);
		ft_free_word(cmd->word);
		ft_free_word(cmd->redir);
		free(cmd);
		cmd = NULL;
	}
}

void		ft_free_arg(t_args *arg)
{
	if (!arg)
		return ;
	ft_free_cmd(arg->cmd);
	arg->cmd = NULL;
	arg->in = -1;
	arg->out = -1;
	arg->err = -1;
	if (arg->str)
	{
		free(arg->str);
		arg->str = NULL;
	}
}
