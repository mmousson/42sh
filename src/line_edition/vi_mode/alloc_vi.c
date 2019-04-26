/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_vi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:59:39 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/26 12:59:47 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "line_edition.h"

int				ft_hash_insert(void)
{
	char		*fresh;

	if (g_env.len >= BUFF_SIZE)
		return (0);
	g_env.mode->v_visual = 0;
	g_env.mode->v_yank = 0;
	if (!(fresh = ft_strnew(g_env.len + 1)))
		ft_errorterm(TMALLOC);
	ft_strncpy(fresh, g_env.line, g_env.p_size);
	fresh[g_env.p_size] = '#';
	ft_strcpy(&(fresh[g_env.p_size + 1]), &(g_env.line[g_env.p_size]));
	ft_strdel(&(g_env.line));
	g_env.line = fresh;
	ft_reset_history();
	ft_strdel(&g_env.oldline);
	if (!(g_env.oldline = ft_strdup(g_env.line)))
		ft_errorterm(TMALLOC);
	return (0);
}

char			*ft_replace_str(char *str, int len)
{
	char		*fresh;
	int			lenstr;

	lenstr = (int)ft_strlen(str);
	if (!(fresh = ft_strnew(len)))
		ft_errorterm(TMALLOC);
	ft_strncpy(fresh, g_env.line, g_env.cm->pos);
	ft_strcpy(&(fresh[g_env.cm->pos]), str);
	ft_strcpy(&(fresh[g_env.cm->pos + lenstr]),
			&(g_env.line[g_env.cm->pos + lenstr]));
	ft_strdel(&(g_env.line));
	return (fresh);
}

void			ft_init_undo(void)
{
	if (g_env.mode->undo)
		return ;
	if (!(g_env.mode->undo = (t_undo*)ft_memalloc(sizeof(t_undo))))
		ft_errorterm(TMALLOC);
	if (!(g_env.mode->undo->command = ft_get_prompt(g_env.prompt)))
		ft_errorterm(TMALLOC);
	g_env.mode->undo->pos = g_env.prompt;
	g_env.mode->undo->next = NULL;
}

void			ft_add_undo(void)
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
		ft_errorterm(TMALLOC);
	if (!(g_env.mode->undo->next->command = ft_strdup(g_env.line)))
		ft_errorterm(TMALLOC);
	g_env.mode->undo->next->pos = g_env.cm->pos;
	g_env.mode->undo->next->next = NULL;
	g_env.mode->undo = tmp;
}

int				ft_delundo(void)
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
