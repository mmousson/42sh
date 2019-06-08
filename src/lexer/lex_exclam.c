/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_exclam.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 17:54:10 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/07 16:19:51 by oboutrol         ###   ########.fr       */
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
	if ((*str)[stat->k] == '!')
	{
		(stat->k)++;
		return (ft_strdup("!"));
	}
	while (ft_isdigit((*str)[stat->k])
			|| (was_char && ft_isalpha((*str)[stat->k])))
	{
		lex_add_char(buff, &sub, (*str)[stat->k]);
		(stat->k)++;
	}
	if (memory != stat->k)
	{
		if (!sub)
			sub = ft_strdup(buff);
		else
			sub = ft_strjoin(sub, buff);
	}
	return (sub);
}

static int	event_not_found(char *event)
{
	ft_putstr_fd("42sh: !", 2);
	ft_putstr_fd(event, 2);
	ft_putstr_fd(": event not found\n", 2);
	return (1);
}

int			is_in_brac(t_stat *stats, char *str)
{
	int		k;
	int		stat;
	int		brac;

	brac = 0;
	k = -1;
	while (++k < stats->k)
	{
		if (str[k] == '\'' && !(stat == 3 || (k > 0 && str[k - 1] == '\\')))
			stat = stat == 1 ? 0 : 1;
		if (str[k] == '"' && !(stat == 1 || (k > 0 && str[k - 1] == '\\')))
			stat = stat == 3 ? 0 : 3;
		if (str[k] == '[' && (k <= 0 || str[k - 1] != '\\') && !(stat % 2))
			brac = 1;
		if (str[k] == ']' && (k <= 0 || str[k - 1] != '\\') && !(stat % 2))
			brac = 0;
	}
	return (brac);
}

int			lex_exclam(t_stat *stat, t_tok **token, char **str)
{
	int		mem;
	char	*start;
	char	*sub;
	char	*old_sub;
	char	*end;

	if (is_in_brac(stat, *str))
		return (1);
	mem = stat->k;
	if ((old_sub = lex_following(str, stat)))
	{
		ft_putendl(old_sub);
		lex_free_token(*token);
		*token = lex_init_token();
		start = ft_strsub(*str, 0, mem);
		sub = hist_getexpend(&old_sub);
		ft_putendl(sub);
		if (!sub || !old_sub || !ft_strcmp(sub, old_sub))
			return (event_not_found(old_sub));
		end = ft_strdup(*str + stat->k);
		if (sub)
			start = ft_strjoinf(start, sub);
		free(*str);
		*str = ft_strjoin(start, end);
		stat->old_status = 0;
		stat->k = -1;
		stat->status = 0;
		ft_strdel(&start);
		ft_strdel(&end);
		ft_strdel(&sub);
		return (0);
	}
	//else
	//	return (event_not_found(old_sub));
	stat->k = mem;
	stat->status = lex_last_pile(stat);
	return (1);
}
