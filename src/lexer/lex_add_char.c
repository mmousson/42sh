/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_add_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:02:48 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/15 11:18:21 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include <stdlib.h>
#include "libft.h"
#include "expand.h"

static int	is_sepa(int status)
{
	if (status == ESP || status == PIP || status == SMC)
		return (1);
	else if (status == ESP + DBL || status == PIP + DBL)
		return (1);
	return (0);
}

int			lex_add_tok(char buf[BUF], t_stat *stat, int status, char **str)
{
	char	*elmt;

	if (get_sub_type(status) == CHAR)
		(stat->cmd)++;
	else if (is_sepa(status))
		stat->cmd = 0;
	if (stat->load)
		elmt = ft_strjoin(stat->load, buf);
	else
		elmt = ft_strdup(buf);
	buf[0] = '\0';
	if (stat->cmd == 1 && expand_alias(str, elmt, stat))
	{
		lex_free_token(*stat->tok);
		*stat->tok = lex_init_token();
		return (1);
	}
	lex_add_arg_token(*stat->tok, elmt, status);
	return (0);
}

void		lex_add_char(char buf[BUF], char **load, char cha)
{
	int		size;
	char	*tmp;

	size = ft_strlen(buf);
	if (size >= BUF - 1)
	{
		if (!(*load))
			*load = ft_strdup(buf);
		else
		{
			tmp = *load;
			*load = ft_strjoin(*load, buf);
			free(tmp);
		}
		ft_bzero(buf, BUF);
		buf[0] = cha;
	}
	else
	{
		buf[size] = cha;
		buf[size + 1] = 0;
	}
}
