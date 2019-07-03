/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 20:11:08 by oboutrol          #+#    #+#             */
/*   Updated: 2019/07/03 17:00:25 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "job_control_42.h"
#include "lex.h"

int				lex_step(t_stat **stat, char **str)
{
	(*stat)->cha = (*str)[(*stat)->k];
	(*stat)->ch = lex_get_ch((*stat)->cha);
	(*stat)->older_status = (*stat)->old_status;
	(*stat)->old_status = (*stat)->status;
	(*stat)->status = lex_get_next_state((*stat)->status, (*stat)->ch);
	if ((*stat)->status == EN || (*stat)->status == EP)
		return (0);
	if ((*stat)->status == -1)
		return (0);
	return (1);
}

static void		lex_following(char **str, t_tok *tok, char ***arge, t_stat *sta)
{
	if (sta->exclam)
		ft_putendl_fd(*str, 2);
	lex_free_stat(sta);
	if (g_env.ctrld && g_env.jobs == 1)
	{
		ft_putendl_fd("There are still jobs active:\n", 2);
		blt_jobs(1, NULL, NULL);
		ft_putendl_fd("\nA second attempt to exit will terminate them.", 2);
	}
	if ((!str || !(*str[0])) && g_env.ctrld
			&& (!g_active_job_list || g_env.jobs > 1))
	{
		lex_free_token(tok);
		ft_strdel(str);
		blt_exit(1, NULL, arge);
	}
	pars_tok(tok, arge);
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

	if ((*stat)->status == EP || (*stat)->status == EC)
	{
		ft_putstr_fd("42sh: syntax error near unexpected `", 2);
		(*stat)->status == EP ? ft_putchar_fd(')', 2) : ft_putchar_fd('}', 2);
		ft_putstr_fd("'\n", 2);
		return (clean_out(token, stat, str));
	}
	else if ((*stat)->status == EN)
	{
		if (!(ret = pars_prepars(*token)))
			return (0);
		if (ret == 2)
			if (!(lex_more(*stat, str, 0, 0)))
				return (clean_out(token, stat, str));
	}
	return (1);
}

int				lex_str(char **str, char ***arge)
{
	t_tok		*token;
	t_stat		*stat;
	char		buff[BUF];
	int			ret;

	if ((ret = 0) || !str || !(*str))
		return (0);
	if (!(token = lex_init_token()))
		return (1);
	if (!(stat = lex_init_stat()))
		return (1);
	stat->tok = &token;
	buff[0] = '\0';
	while (stat->status != EN && stat->status != EP && stat->status != -1)
	{
		if (lex_step(&stat, str))
			if ((ret = lex_proc(stat, buff, str)) == -1)
				if (!(lex_more(stat, str, 1, ret)))
					return (clean_out(&token, &stat, str));
		if (ret != 1 && !(lex_last(&stat, &token, str)))
			return (clean_out(&token, &stat, str));
		(stat->k)++;
	}
	lex_following(str, token, arge, stat);
	return (0);
}
