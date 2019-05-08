/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:59:39 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/02 16:04:11 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "line_edition.h"

void			vi_init_undo(void)
{
	if (g_env.mode->undo)
		return ;
	if (!(g_env.mode->undo = (t_undo*)ft_memalloc(sizeof(t_undo))))
		sh_errorterm(TMALLOC);
	if (!(g_env.mode->undo->command = line_get_prompt(g_env.prompt)))
		sh_errorterm(TMALLOC);
	g_env.mode->undo->pos = g_env.prompt;
	g_env.mode->undo->next = NULL;
}

void			vi_add_undo(void)
{
	t_undo		*tmp;

	if (!g_env.mode->undo)
		return ;
	tmp = g_env.mode->undo;
	while (g_env.mode->undo->next)
		g_env.mode->undo = g_env.mode->undo->next;
	if (!ft_strcmp(g_env.mode->undo->command, g_env.line))
	{
		g_env.mode->undo = tmp;
		return ;
	}
	if (!(g_env.mode->undo->next = (t_undo*)ft_memalloc(sizeof(t_undo))))
		sh_errorterm(TMALLOC);
	if (!(g_env.mode->undo->next->command = ft_strdup(g_env.line)))
		sh_errorterm(TMALLOC);
	g_env.mode->undo->next->pos = g_env.cm->pos;
	g_env.mode->undo->next->next = NULL;
	g_env.mode->undo = tmp;
}

int				vi_delundo(void)
{
	t_undo		*tmp;

	if (!g_env.mode->undo)
		return (0);
	tmp = g_env.mode->undo;
	while (g_env.mode->undo->next && g_env.mode->undo->next->next)
		g_env.mode->undo = g_env.mode->undo->next;
	if (!g_env.mode->undo->next)
	{
		ft_strdel(&(g_env.mode->undo->command));
		ft_memdel((void**)&g_env.mode->undo);
		return (0);
	}
	else
	{
		ft_strdel(&(g_env.mode->undo->next->command));
		ft_memdel((void**)&(g_env.mode->undo->next));
		g_env.mode->undo = tmp;
	}
	return (1);
}

int				vi_hash_insert(void)
{
	char		*fresh;

	if (g_env.len >= BUFF_SIZE)
		return (0);
	g_env.mode->v_visual = 0;
	g_env.mode->v_yank = 0;
	if (!(fresh = ft_strnew(g_env.len + 1)))
		sh_errorterm(TMALLOC);
	ft_strncpy(fresh, g_env.line, g_env.p_size);
	fresh[g_env.p_size] = '#';
	ft_strcpy(&(fresh[g_env.p_size + 1]), &(g_env.line[g_env.p_size]));
	ft_strdel(&(g_env.line));
	g_env.line = fresh;
	line_reset_history();
	ft_strdel(&g_env.oldline);
	if (!(g_env.oldline = ft_strdup(g_env.line)))
		sh_errorterm(TMALLOC);
	return (0);
}
