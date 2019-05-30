/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_prior_flag.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 17:04:26 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/30 11:02:18 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

static void		vi_prior_r(char *str)
{
	int			count;
	char		*fresh;

	count = g_env.count;
	if (count > g_env.len - g_env.cm->pos)
		count = g_env.len - g_env.cm->pos;
	if (!(fresh = ft_strnew(1)))
		sh_errorterm(TMALLOC);
	while (--count + 1)
		if (!(fresh = ft_strjoinf(fresh, str)))
		{
			ft_strdel(&fresh);
			sh_errorterm(TMALLOC);
		}
	g_env.mode->v_replace = 1;
	vi_add_undo();
	line_paste(fresh, 1);
	vi_undo_update_pos();
	g_env.mode->v_replace = 0;
	g_env.mode->v_replace_one = 0;
	ft_strdel(&fresh);
}

static void		vi_fftt(char *str, int i)
{
	vi_jump_occur(str[0], i, g_env.count);
	g_env.mode->v_lasta = str[0];
	i = -1;
	while (++i < 4)
		g_env.mode->v_prior[i] = 0;
	if (g_env.mode->v_del)
		vi_cdel();
	if (g_env.mode->v_yank)
		vi_cpy();
}

int				vi_get_prior_flag(char *str, int ret)
{
	int			i;

	i = -1;
	while (++i < 4)
		if (g_env.mode->v_prior[i])
			break ;
	if ((i == 4 && !g_env.mode->v_replace_one) || ret != 1)
		return (0);
	if (g_env.mode->v_replace_one)
		vi_prior_r(str);
	else
		vi_fftt(str, i);
	vi_reset_count(str);
	return (1);
}
