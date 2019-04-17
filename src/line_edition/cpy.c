/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 02:36:49 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/10 17:17:07 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"
#include "libft.h"

void				ft_init_cpy(t_env *env)
{
	env->mode->n_select = 1;
	env->cpy->pos = env->cm->pos;
}

static void			ft_escap_cpy(t_env *env, int move_cursor)
{
	env->mode->n_select = 0;
	if (!move_cursor || env->cm->pos == env->cpy->pos)
		return ;
	if (env->cm->pos < env->cpy->pos)
		ft_cursor_motion(env, MRIGHT, env->cpy->pos - env->cm->pos);
	else
		ft_cursor_motion(env, MLEFT, env->cm->pos - env->cpy->pos);
}

static void			ft_cpy(t_env *env, int ctrlc)
{
	char			*cpy;
	int				min;
	int				max;

	if (env->cm->pos == env->cpy->pos)
		return ;
	min = env->cpy->pos > env->cm->pos ? env->cm->pos : env->cpy->pos;
	max = min == env->cm->pos ? env->cpy->pos : env->cm->pos;
	if (!(cpy = ft_strsub(env->line, min, max - min)))
		ft_errorterm(TMALLOC, env);
	ft_strdel(&(env->cpy->str));
	env->cpy->str = cpy;
	if (ctrlc)
		ft_escap_cpy(env, 1);
}

static void			ft_cut(t_env *env)
{
	if (env->cm->pos == env->cpy->pos)
		return ;
	ft_cpy(env, 0);
	if (env->cpy->pos < env->cm->pos)
	{
		env->line = ft_delchar(env, env->cm->pos - env->cpy->pos);
		ft_cursor_motion(env, MLEFT, env->cpy->pos - env->cm->pos);
		ft_escap_cpy(env, 1);
	}
	else
	{
		env->line = ft_delchar_bs(env, env->cpy->pos - env->cm->pos);
		ft_cursor_motion(env, MLEFT, env->cm->pos - env->cpy->pos);
		ft_escap_cpy(env, 0);
	}
}

int					ft_line_cpy(t_env *env, char *str, int ret)
{
	if (str[0] == 27 && ret == 1)
		ft_escap_cpy(env, 1);
	else if (ft_isaltc(str))
		ft_cpy(env, 1);
	else if (ft_isaltx(str))
		ft_cut(env);
	ft_line_arrow(env, str);
	return (1);
}
