/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 10:09:40 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/21 18:20:07 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

void				hist_add(char *str)
{
	t_history		*tmp;
	t_history		*new;

	tmp = g_env.ry;
	if (!(new = (t_history*)ft_memalloc(sizeof(t_history))))
		sh_errorterm(TMALLOC);
	new->next = tmp;
	new->prev = NULL;
	if (tmp)
		tmp->prev = new;
	if (!(new->line = ft_strdup(str)))
		sh_errorterm(TMALLOC);
	g_env.ry = new;
}

void				hist_alloc_search(t_prompt prompt)
{
	char			*fresh;
	char			*fresh_p;

	if (!(fresh_p = line_get_prompt(prompt)))
		sh_errorterm(TMALLOC);
	if (!(fresh = (char*)malloc(sizeof(char)
					* (g_env.len - g_env.p_size + prompt - g_env.h_len))))
		sh_errorterm(TMALLOC);
	ft_strcpy(fresh, fresh_p);
	ft_strcpy(&(fresh[prompt]), &(g_env.line[g_env.p_size + g_env.h_len]));
	g_env.cm->pos = g_env.cm->pos - g_env.p_size + prompt - g_env.h_len;
	ft_strdel(&g_env.line);
	ft_strdel(&fresh_p);
	g_env.line = fresh;
	g_env.p_size = prompt;
	g_env.prompt = prompt;
	g_env.len = (int)ft_strlen(fresh);
}

char				*hist_addstr(char *str)
{
	char			*fresh;
	int				len;
	int				lenstr;

	if (!g_env.h_word)
		g_env.h_word = ft_strdup(str);
	else
		g_env.h_word = ft_strjoinf(g_env.h_word, str);
	if (!g_env.h_word)
		sh_errorterm(TMALLOC);
	lenstr = (int)ft_strlen(str);
	len = (int)ft_strlen(g_env.line) + lenstr;
	g_env.h_len = (int)ft_strlen(g_env.h_word);
	if (len > BUFF_SIZE - 10)
		return (g_env.line);
	if (!(fresh = ft_strnew(len)))
		sh_errorterm(TMALLOC);
	ft_strncpy(fresh, g_env.line, g_env.h_len + 19);
	ft_strcpy(&(fresh[g_env.h_len + 19]), str);
	ft_strcpy(&(fresh[g_env.h_len + 19 + lenstr]),
			&(g_env.line[g_env.h_len + 19]));
	ft_strdel(&(g_env.line));
	return (fresh);
}

char				*hist_delchar(void)
{
	char			*fresh;
	char			*tmp;

	if (g_env.cm->pos <= g_env.p_size || !g_env.h_len)
		return (g_env.line);
	if (!(fresh = ft_strnew(g_env.len - 1)))
		sh_errorterm(TMALLOC);
	if (!(tmp = ft_strsub(g_env.h_word, 0, g_env.h_len - 1)))
		sh_errorterm(TMALLOC);
	ft_strdel(&g_env.h_word);
	g_env.h_word = tmp;
	g_env.h_len--;
	ft_strncpy(fresh, g_env.line, 20 + g_env.h_len);
	ft_strcpy(&(fresh[20 + g_env.h_len]), &(g_env.line[20 + g_env.h_len + 1]));
	ft_strdel(&(g_env.line));
	return (fresh);
}
