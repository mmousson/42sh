/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_exclam.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 17:54:10 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/19 17:14:58 by oboutrol         ###   ########.fr       */
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

	sub = NULL;
	ft_bzero(buff, BUF);
	stat->k++;
	process_sign(str, stat, &sub, buff);
	was_char = ft_isalpha((*str)[stat->k]);
	while (ft_isdigit((*str)[stat->k])
			|| (was_char && ft_isalpha((*str)[stat->k])))
	{
		lex_add_char(buff, &sub, (*str)[stat->k]);
		(stat->k)++;
	}
	if (!sub)
		sub = ft_strdup(buff);
	else
		sub = ft_strjoin(sub, buff);
	return (sub);
}

int			lex_exclam(t_stat *stat, t_tok **token, char **str)
{
	int		mem;
	char	*start;
	char	*sub;
	char	*end;

	mem = stat->k;
	if ((sub = lex_following(str, stat)))
	{
		lex_free_token(*token);
		*token = lex_init_token();
		start = ft_strsub(*str, 0, mem);
		sub = hist_getexpend(&sub);
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
	stat->k = mem;
	stat->status = CHA;
	return (1);
}
