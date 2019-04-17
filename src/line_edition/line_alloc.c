/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 22:52:39 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/06 19:14:29 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"
#include <stdlib.h>
#include "libft.h"

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
	return (NULL);
}

char				*ft_addstr(t_env *env, char *str)
{
	char			*fresh;
	int				len;

	len = env->len + (int)ft_strlen(str);
	if (len > BUFF_SIZE - 10)
		return (env->line);
	if (!(fresh = ft_strnew(len)))
		ft_errorterm(TMALLOC, env);
	ft_strncpy(fresh, env->line, env->cm->pos);
	ft_strcpy(&(fresh[env->cm->pos]), str);
	ft_strcpy(&(fresh[env->cm->pos + (int)ft_strlen(str)]),
			&(env->line[env->cm->pos]));
	ft_strdel(&(env->line));
	return (fresh);
}

char				*ft_delchar(t_env *env, int size)
{
	char			*fresh;

	if (env->cm->pos <= env->p_size)
		return (env->line);
	if (!(fresh = ft_strnew(env->len - size)))
		ft_errorterm(TMALLOC, env);
	ft_strncpy(fresh, env->line, env->cm->pos - size);
	ft_strcpy(&(fresh[env->cm->pos - size]), &(env->line[env->cm->pos]));
	ft_strdel(&(env->line));
	return (fresh);
}

char				*ft_delchar_bs(t_env *env, int size)
{
	char			*fresh;

	if (env->cm->pos == env->len)
		return (env->line);
	if (!(fresh = ft_strnew(env->len - size)))
		ft_errorterm(TMALLOC, env);
	ft_strncpy(fresh, env->line, env->cm->pos);
	ft_strcpy(&(fresh[env->cm->pos]), &(env->line[env->cm->pos + size]));
	ft_strdel(&(env->line));
	return (fresh);
}

char				*ft_alloc_history(t_env *env, int stline)
{
	char			*prompt;

	if (stline && env->oldline)
	{
		ft_strdel(&(env->line));
		return (ft_strdup(env->oldline));
	}
	if (!(prompt = ft_get_prompt(env->prompt)))
		ft_errorterm(TMALLOC, env);
	ft_strdel(&(env->line));
	return (ft_strjoinf(prompt, env->ry->line));
}
