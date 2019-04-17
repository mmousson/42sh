/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 21:42:23 by oboutrol          #+#    #+#             */
/*   Updated: 2019/03/20 03:33:22 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexpars.h"

void		ft_print_stat(int stat)
{
	ft_putchar('_');
	ft_putnbr(stat);
}

void		ft_print_word(t_word *word)
{
	t_word	*tmp;
	int		nfirst;

	tmp = word;
	nfirst = 0;
	ft_putchar('{');
	while (word)
	{
		if (nfirst)
			ft_putstr(", ");
		nfirst = 1;
		if (word->value)
			ft_putstr(word->value);
		if (word->type > 1)
			ft_print_stat(word->type);
		word = word->next;
	}
	ft_putchar('}');
	word = tmp;
}

void		ft_print_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		nfirst;

	tmp = cmd;
	nfirst = 0;
	while (cmd)
	{
		if (nfirst)
			ft_putchar('\n');
		nfirst = 1;
		ft_print_word(cmd->word);
		ft_putstr(" --> ");
		ft_print_word(cmd->redir);
		if (cmd->pipe)
			ft_putstr(" piped with >");
		cmd = cmd->next;
	}
	ft_putchar('\n');
	cmd = tmp;
}
