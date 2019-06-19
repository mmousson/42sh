/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 22:52:39 by roliveir          #+#    #+#             */
/*   Updated: 2019/06/09 20:09:03 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

char				*line_get_prompt(t_prompt prompt)
{
	if (prompt == PBASIC)
		return (ft_strdup("$> "));
	else if (prompt == PQUOTE)
		return (ft_strdup("quote> "));
	else if (prompt == PDQUOTE)
		return (ft_strdup("dquote> "));
	else if (prompt == PPIPE)
		return (ft_strdup("pipe> "));
	else if (prompt == PHEREDOC)
		return (ft_strdup("heredoc> "));
	else if (prompt == PBACKS)
		return (ft_strdup("bs> "));
	else if (prompt == PDEF)
		return (ft_strdup("> "));
	else if (prompt == HIST)
		return (ft_strdup("(search in history)`': "));
	return (NULL);
}

char				*line_addstr(char *str)
{
	char			*fresh;
	int				len;
	int				lenstr;

	lenstr = (int)ft_strlen(str);
	len = (int)ft_strlen(g_env.line) + lenstr;
	if (g_env.mode->v_replace && g_env.cm->pos < len - lenstr)
		return (vi_replace_str(str, len));
	if (len > BUFF_SIZE - 10)
		return (g_env.line);
	if (!(fresh = ft_strnew(len)))
		sh_errorterm(TMALLOC);
	ft_strncpy(fresh, g_env.line, g_env.cm->pos);
	ft_strcpy(&(fresh[g_env.cm->pos]), str);
	ft_strcpy(&(fresh[g_env.cm->pos + lenstr]),
			&(g_env.line[g_env.cm->pos]));
	ft_strdel(&(g_env.line));
	return (fresh);
}

char				*line_delchar(int size)
{
	char			*fresh;

	if (g_env.cm->pos <= g_env.p_size)
		return (g_env.line);
	if (size > g_env.cm->pos - g_env.p_size)
		size = g_env.cm->pos - g_env.p_size;
	if (g_env.mode->saved)
		ft_strncpy(g_env.s_buffer, &(g_env.line[g_env.cm->pos - size]), size);
	if (size > 1 && g_env.mode->mode[MNORMAL])
	{
		ft_strncpy(&(g_env.s_buffkill[g_env.k_index]),
				&(g_env.line[g_env.cm->pos - size]), size);
		g_env.k_index += size;
		g_env.s_buffkill[g_env.k_index] = '\0';
	}
	if (!(fresh = ft_strnew(g_env.len - size)))
		sh_errorterm(TMALLOC);
	ft_strncpy(fresh, g_env.line, g_env.cm->pos - size);
	ft_strcpy(&(fresh[g_env.cm->pos - size]), &(g_env.line[g_env.cm->pos]));
	ft_strdel(&(g_env.line));
	return (fresh);
}

char				*line_delchar_bs(int size)
{
	char			*fresh;

	if (g_env.cm->pos == g_env.len - 1)
		return (g_env.line);
	if (size > g_env.len - g_env.cm->pos)
		size = g_env.len - g_env.cm->pos;
	if (g_env.mode->saved)
		ft_strncpy(g_env.s_buffer, &(g_env.line[g_env.cm->pos]), size);
	if (size > 1 && g_env.mode->mode[MNORMAL])
	{
		ft_strncpy(&(g_env.s_buffkill[g_env.k_index]),
				&(g_env.line[g_env.cm->pos]), size);
		g_env.k_index += size;
		g_env.s_buffkill[g_env.k_index] = '\0';
	}
	if (!(fresh = ft_strnew(g_env.len - size)))
		sh_errorterm(TMALLOC);
	ft_strncpy(fresh, g_env.line, g_env.cm->pos);
	ft_strcpy(&(fresh[g_env.cm->pos]), &(g_env.line[g_env.cm->pos + size]));
	ft_strdel(&(g_env.line));
	return (fresh);
}

char				*line_alloc_history(int stline)
{
	char			*prompt;
	char			*tmp;

	if (stline && g_env.oldline)
	{
		ft_strdel(&(g_env.line));
		return (ft_strdup(g_env.oldline));
	}
	if (!(prompt = line_get_prompt(g_env.prompt)))
		sh_errorterm(TMALLOC);
	ft_strdel(&(g_env.line));
	if ((int)ft_strlen(g_env.ry->line) < BUFF_SIZE)
		return (ft_strjoinf(prompt, g_env.ry->line));
	tmp = ft_strsub(g_env.ry->line, 0, BUFF_SIZE - (int)ft_strlen(prompt));
	ft_strdel(&g_env.ry->line);
	g_env.ry->line = tmp;
	return (ft_strjoinf(prompt, g_env.ry->line));
}
