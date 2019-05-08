/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 20:11:08 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/04 17:18:53 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

static void		ft_step_lex(t_stat **stat, char **str)
{
	(*stat)->cha = (*str)[(*stat)->k];
	(*stat)->ch = ft_get_ch((*stat)->cha);
	(*stat)->old_status = (*stat)->status;
	(*stat)->status = ft_get_next_state((*stat)->status, (*stat)->ch);
}

static void		ft_following(char **str, t_tok *tok, char ***arge)
{
	if ((!str || *str == NULL || *str[0] == 0) && g_env.ctrld)
	{
		ft_free_token(tok);
		ft_strdel(str);
		ft_del_words_tables(arge);
		sh_quiterm();
	}
	ft_pars(tok, arge, *str);
	ft_free_token(tok);
}

int				clean_out(t_tok **token, t_stat **stat, char **str)
{
	ft_free_token(*token);
	*token = NULL;
	ft_free_stat(*stat);
	*stat = NULL;
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
	return (0);
}

static int		ft_last_lex(t_stat **stat, t_tok **token, char **str)
{
	int			ret;

	if ((*stat)->status == EN)
	{
		if (!(ret = ft_prepars(*token)))
			return (0);
		if (ret == 2)
			if (!(ft_more(*stat, str, 0)))
				return (clean_out(token, stat, str));
	}
	return (1);
}

int				ft_lex(char **str, char ***arge)
{
	t_tok		*token;
	t_stat		*stat;
	char		buff[BUF];

	if (!str || !(*str))
		return (0);
	if (!(token = ft_init_token()))
		return (1);
	if (!(stat = ft_init_stat()))
		return (1);
	buff[0] = '\0';
	while (stat->status != EN)
	{
		ft_step_lex(&stat, str);
		if (stat->status != EN)
			if (proc(stat, buff, token) == -1)
				if (!(ft_more(stat, str, 1)))
					return (clean_out(&token, &stat, str));
		if (!(ft_last_lex(&stat, &token, str)))
			return (clean_out(&token, &stat, str));
		(stat->k)++;
	}
	ft_free_stat(stat);
	ft_following(str, token, arge);
	return (0);
}
