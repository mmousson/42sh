/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_exclam.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 17:54:10 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/14 17:58:39 by oboutrol         ###   ########.fr       */
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
	int		type;
	int		og_type;
	char	*sub;
	char	buff[BUF];
	int		p;

	sub = NULL;
	ft_bzero(buff, BUF);
	p = 0;
	stat->k++;
	process_sign(str, stat, &sub, buff);
	type = lex_get_ch((*str)[stat->k]);
	og_type = type;
	if (type != CHA && type != INT)
		return (NULL);
	while (type == og_type || type == INT)
	{
		lex_add_char(buff, &sub, (*str)[stat->k]);
		(stat->k)++;
		type = lex_get_ch((*str)[stat->k]);
	}
	if (!sub)
		sub = ft_strdup(buff);
	else
		sub = ft_strjoin(sub, buff);
	return (sub);
}

char		*history_expand(char *sub)//a remplacer par la ft history exp
{
	char	*expand;

	expand = ft_strjoin("__", sub);
	free(sub);
	expand = ft_strjoinf(expand, "__");
	return (expand);
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
