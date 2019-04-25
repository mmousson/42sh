/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 22:52:39 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/25 10:46:23 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"
#include <stdlib.h>

char				*ft_get_prompt(t_prompt prompt)
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
	return (NULL);
}

char				*ft_addstr(char *str)
{
	char			*fresh;
	int				len;

	len = (int)ft_strlen(g_env.line) + (int)ft_strlen(str);
	if (len > BUFF_SIZE - 10)
		return (g_env.line);
	if (g_env.mode->v_replace)
		return (ft_replace_str(str, len));
	if (!(fresh = ft_strnew(len)))
		ft_errorterm(TMALLOC);
	ft_strncpy(fresh, g_env.line, g_env.cm->pos);
	ft_strcpy(&(fresh[g_env.cm->pos]), str);
	ft_strcpy(&(fresh[g_env.cm->pos + (int)ft_strlen(str)]),
			&(g_env.line[g_env.cm->pos]));
	ft_strdel(&(g_env.line));
	return (fresh);
}

char				*ft_delchar(int size)
{
	char			*fresh;

	if (g_env.cm->pos <= g_env.p_size)
		return (g_env.line);
	if (size > g_env.cm->pos - g_env.p_size)
		size = g_env.cm->pos - g_env.p_size;
	if (g_env.mode->saved)
		ft_strncpy(g_env.mode->s_buffer, &(g_env.line[g_env.cm->pos]), size);
	if (!(fresh = ft_strnew(g_env.len - size)))
		ft_errorterm(TMALLOC);
	ft_strncpy(fresh, g_env.line, g_env.cm->pos - size);
	ft_strcpy(&(fresh[g_env.cm->pos - size]), &(g_env.line[g_env.cm->pos]));
	ft_strdel(&(g_env.line));
	return (fresh);
}

char				*ft_delchar_bs(int size)
{
	char			*fresh;

	if (g_env.cm->pos == g_env.len)
		return (g_env.line);
	if (size > g_env.len - g_env.cm->pos)
		size = g_env.len - g_env.cm->pos;
	if (g_env.mode->saved)
		ft_strncpy(g_env.mode->s_buffer, &(g_env.line[g_env.cm->pos]), size);
	if (!(fresh = ft_strnew(g_env.len - size)))
		ft_errorterm(TMALLOC);
	ft_strncpy(fresh, g_env.line, g_env.cm->pos);
	ft_strcpy(&(fresh[g_env.cm->pos]), &(g_env.line[g_env.cm->pos + size]));
	ft_strdel(&(g_env.line));
	return (fresh);
}

char				*ft_alloc_history(int stline)
{
	char			*prompt;

	if (stline && g_env.oldline)
	{
		ft_strdel(&(g_env.line));
		return (ft_strdup(g_env.oldline));
	}
	if (!(prompt = ft_get_prompt(g_env.prompt)))
		ft_errorterm(TMALLOC);
	ft_strdel(&(g_env.line));
	return (ft_strjoinf(prompt, g_env.ry->line));
}
