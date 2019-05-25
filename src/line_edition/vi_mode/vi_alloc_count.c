/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_alloc_count.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 15:10:32 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/19 09:43:55 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

static void		vi_initcount(char *nbr, char *fresh)
{
	ft_strncpy(fresh, g_env.line, g_env.p_size);
	ft_strcpy(&(fresh[g_env.p_size]), "(");
	ft_strcpy(&(fresh[g_env.p_size + 1]), nbr);
	ft_strcpy(&(fresh[g_env.p_size + 2]), ") ");
	ft_strcpy(&(fresh[g_env.p_size + 4]), &(g_env.line[g_env.p_size]));
}

static void		vi_updatecount(int len, char *nbr, char *fresh)
{
	ft_strncpy(fresh, g_env.line, g_env.p_size + 1);
	ft_strcpy(&(fresh[g_env.p_size + 1]), nbr);
	ft_strcpy(&(fresh[g_env.p_size + 1 + len]), ") ");
	ft_strcpy(&(fresh[g_env.p_size + 3 + len]),
			&(g_env.line[g_env.p_size + len + 2]));
}

void			vi_alloc_count(void)
{
	char		*fresh;
	char		*nbr;
	int			len;
	int			msize;

	if (g_env.len + 1 > BUFF_SIZE)
		return ;
	len = ft_count_n(g_env.count);
	msize = len == 1 ? 4 : 1;
	if (!(fresh = ft_strnew(g_env.len + msize)))
		sh_errorterm(TMALLOC);
	if (!(nbr = ft_itoa(g_env.count)))
		sh_errorterm(TMALLOC);
	if (len == 1)
		vi_initcount(nbr, fresh);
	else
		vi_updatecount(len, nbr, fresh);
	ft_strdel(&nbr);
	ft_strdel(&g_env.line);
	g_env.line = fresh;
	line_cursor_motion(MRIGHT, msize == 4 ? 4 : 1);
}

int				vi_del_count(void)
{
	char		*fresh;
	int			len;

	if (g_env.line[g_env.p_size] != '(' || (!g_env.mode->v_command
					&& g_env.count < 2))
		return (1);
	len = ft_count_n(g_env.count) + 3;
	g_env.mode->v_command = 0;
	if (!(fresh = ft_strnew(g_env.len - len)))
		sh_errorterm(TMALLOC);
	ft_strncpy(fresh, g_env.line, g_env.p_size);
	ft_strcpy(&(fresh[g_env.p_size]), &(g_env.line[g_env.p_size + len]));
	ft_strdel(&g_env.line);
	g_env.line = fresh;
	line_cursor_motion(MLEFT, len);
	return (1);
}
