/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 20:11:08 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/18 14:09:11 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include "pars.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

static int		lex_step(t_stat **stat, char **str)
{
	(*stat)->cha = (*str)[(*stat)->k];
	(*stat)->ch = lex_get_ch((*stat)->cha);
	(*stat)->old_status = (*stat)->status;
	(*stat)->status = lex_get_next_state((*stat)->status, (*stat)->ch);
	if ((*stat)->status == EN || (*stat)->status == EP)
		return (0);
	if ((*stat)->status == -1)
		return (0);
	return (1);
}

static void		lex_following(char **str, t_tok *tok, char ***arge)
{
	if ((!str || *str == NULL || *str[0] == 0) && g_env.ctrld)
	{
		lex_free_token(tok);
		ft_strdel(str);
		ft_del_words_tables(arge);
		sh_quiterm();
	}
	pars_tok(tok, arge, *str);
	lex_free_token(tok);
}

int				clean_out(t_tok **token, t_stat **stat, char **str)
{
	lex_free_token(*token);
	*token = NULL;
	lex_free_stat(*stat);
	*stat = NULL;
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
	return (0);
}

static int		lex_last(t_stat **stat, t_tok **token, char **str)
{
	int			ret;

	if ((*stat)->status == EP)
	{
		ft_putstr_fd("42sh: do not support '()'\n", 2);
		return (clean_out(token, stat, str));
	}
	else if ((*stat)->status == EN)
	{
		if (!(ret = pars_prepars(*token)))
			return (0);
		if (ret == 2)
			if (!(lex_more(*stat, str, 0)))
				return (clean_out(token, stat, str));
	}
	return (1);
}

int				lex_str(char **str, char ***arge)
{
	t_tok		*token;
	t_stat		*stat;
	char		buff[BUF];

	if (!str || !(*str))
		return (0);
	if (!(token = lex_init_token()))
		return (1);
	if (!(stat = lex_init_stat()))
		return (1);
	buff[0] = '\0';
	while (stat->status != EN && stat->status != EP && stat->status != -1)
	{
		if (lex_step(&stat, str))
			if (lex_proc(stat, buff, &token, str) == -1)
				if (!(lex_more(stat, str, 1)))
					return (clean_out(&token, &stat, str));
		if (!(lex_last(&stat, &token, str)))//regarder le case pile not empty
			return (clean_out(&token, &stat, str));
		(stat->k)++;
	}
	lex_free_stat(stat);
	lex_following(str, token, arge);
	return (0);
}
