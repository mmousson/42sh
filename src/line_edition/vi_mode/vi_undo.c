/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_undo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 17:58:52 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/04 16:33:36 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

void				vi_undo_update_pos(void)
{
	t_undo			*tmp;

	if (!g_env.mode->undo)
		return ;
	tmp = g_env.mode->undo;
	while (g_env.mode->undo->next)
		g_env.mode->undo = g_env.mode->undo->next;
	g_env.mode->undo->pos = g_env.cm->pos;
	g_env.mode->undo = tmp;
}

void				vi_reset_cursor(t_undo *tmp, int u)
{
	while (u && tmp->next)
		tmp = tmp->next;
	if (tmp->pos > g_env.cm->pos)
		line_cursor_motion(MRIGHT, tmp->pos - g_env.cm->pos);
	else
		line_cursor_motion(MLEFT, g_env.cm->pos - tmp->pos);
}

static int			vi_lstlen(t_undo *undo)
{
	int				lstlen;

	lstlen = 0;
	while (undo && undo->next)
	{
		undo = undo->next;
		lstlen++;
	}
	return (lstlen);
}

static int			vi_bigu(char *str, int ret)
{
	int				lstlen;
	char			*oldline;

	if (!g_env.mode->undo->next)
		return (0);
	if (str[0] == 'U' && ret == 1)
	{
		lstlen = vi_lstlen(g_env.mode->undo) + 1;
		oldline = g_env.line;
		if (!(g_env.line = ft_strdup(g_env.mode->undo->next->command)))
			sh_errorterm(TMALLOC);
		vi_reset_cursor(g_env.mode->undo, 0);
		while (--lstlen)
			vi_delundo();
		ft_strdel(&oldline);
	}
	else
		return (0);
	return (1);
}

int					vi_undo(char *str, int ret)
{
	t_undo			*tmp;
	char			*oldline;

	if (!g_env.mode->undo)
		return (0);
	if (str[0] == 'u' && ret == 1)
	{
		tmp = g_env.mode->undo;
		oldline = g_env.line;
		while (g_env.mode->undo->next)
			g_env.mode->undo = g_env.mode->undo->next;
		if (!(g_env.line = ft_strdup(g_env.mode->undo->command)))
			sh_errorterm(TMALLOC);
		vi_reset_cursor(tmp, 1);
		g_env.mode->undo = tmp;
		vi_delundo();
		ft_strdel(&oldline);
	}
	else if (vi_bigu(str, ret))
		;
	else
		return (0);
	vi_reset_count(str);
	return (1);
}
