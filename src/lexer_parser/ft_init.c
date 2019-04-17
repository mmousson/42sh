/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 06:09:20 by oboutrol          #+#    #+#             */
/*   Updated: 2019/04/04 13:53:14 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexpars.h"
#include "libft.h"
#include <stdlib.h>

t_word		*init_word(void)
{
	t_word	*word;

	if (!(word = (t_word*)malloc(sizeof(t_word))))
		return (NULL);
	word->next = NULL;
	word->value = NULL;
	word->news = 0;
	word->type = 0;
	return (word);
}

t_cmd		*init_cmd(void)
{
	t_cmd	*cmd;

	if (!(cmd = (t_cmd*)malloc(sizeof(t_cmd))))
		return (NULL);
	cmd->word = init_word();
	cmd->redir = init_word();
	cmd->next = NULL;
	cmd->pipe = 0;
	cmd->status = 1;
	return (cmd);
}

t_args		init_args(char *str, t_env *line, char ***arge)
{
	t_args	arg;

	arg.k = 0;
	arg.arge = arge;
	arg.str = ft_strdup(str);
	arg.cmd = init_cmd();
	arg.status = S_START_SP;
	arg.charac = SPACE;
	arg.line = line;
	arg.agg = 0;
	arg.in = -1;
	arg.out = -1;
	arg.err = -1;
	return (arg);
}
