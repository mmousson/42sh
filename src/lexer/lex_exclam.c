/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_exclam.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 17:54:10 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/09 11:41:32 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include "history.h"

static void	process_sign(char **str, t_stat *stat, char **sub, char buff[BUF])
{
	if ((*str)[stat->k] == '-')
	{
		lex_add_char(buff, sub, (*str)[stat->k]);
		(stat->k)++;
	}
	else if ((*str)[stat->k] == '+')
		(stat->k)++;
}

static char	*lex_following(char **str, t_stat *stat)
{
	int		was_char;
	char	*sub;
	char	buff[BUF];
	int		memory;

	sub = NULL;
	ft_bzero(buff, BUF);
	stat->k++;
	memory = stat->k;
	process_sign(str, stat, &sub, buff);
	was_char = ft_isalpha((*str)[stat->k]);
	if ((*str)[stat->k] == '!' && (stat->k)++)
		return (ft_strdup("!"));
	while (ft_isdigit((*str)[stat->k])
			|| (was_char && ft_isalpha((*str)[stat->k])))
	{
		lex_add_char(buff, &sub, (*str)[stat->k]);
		(stat->k)++;
	}
	if (memory != stat->k)
		sub = sub ? ft_strjoin(sub, buff) : ft_strdup(buff);
	return (sub);
}

static int	event_not_found(char **event)
{
	ft_putstr_fd("42sh: !", 2);
	ft_putstr_fd(*event, 2);
	ft_putstr_fd(": event not found\n", 2);
	ft_strdel(event);
	return (-2);
}

int			is_in_brac(t_stat *stat, char *str)
{
	int		k;

	k = stat->k;
	if (stat->k == 0 || str[stat->k - 1] != '[')
		return (0);
	while (str[++k])
	{
		if (str[k] == ']')
			return (1);
	}
	return (0);
}

int			lex_exclam(t_stat *stat, t_tok **token, char **str, char buff[BUF])
{
	int		mem;
	char	*sub;
	char	*old_sub;

	if (is_in_brac(stat, *str))
	{
		stat->status = stat->old_status;
		return (0);
	}
	mem = stat->k;
	if ((old_sub = lex_following(str, stat)))
	{
		sub = hist_getexpend(&old_sub);
		if (!sub)
			return (event_not_found(&old_sub));
		else
			stat->exclam = 1;
		lex_include(str, &sub, mem, stat->k);
		return (lex_reline(stat, token, buff));
	}
	stat->k = mem;
	stat->status = lex_last_pile(stat);
	return (0);
}
