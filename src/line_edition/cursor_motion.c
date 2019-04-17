/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_motion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 22:32:05 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/07 14:52:40 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"
#include "libft.h"

static void		ft_cursor_left(t_env *env)
{
	env->cm->pos--;
}

static void		ft_cursor_right(t_env *env)
{
	env->cm->pos++;
}

void			ft_cursor_ry(t_env *env)
{
	int			len;

	len = (int)ft_strlen(env->line);
	ft_cursor_motion(env, MRIGHT, len - env->cm->pos);
	ft_cursor_motion(env, MLEFT, env->cm->pos - len);
}

static int		ft_ismoving(t_env *env, t_move move)
{
	int			len;

	len = (int)ft_strlen(env->line);
	if (move == MRIGHT && env->cm->pos < len)
		return (1);
	if (move == MLEFT && len > ft_get_termroom(env)
			&& !env->del && !ft_getx(env, env->cm->pos)
			&& env->cm->pos < ft_get_origin_pos(env))
		return (0);
	if (move == MLEFT && env->cm->pos > env->p_size
			&& (ft_getx(env, env->cm->pos) != 0
				|| ft_gety(env, env->cm->pos) != 0))
		return (1);
	return (0);
}

void			ft_cursor_motion(t_env *env, t_move move, int len)
{
	int			i;

	i = -1;
	while (++i < len)
	{
		if (move == MRIGHT && ft_ismoving(env, move))
			ft_cursor_right(env);
		else if (move == MLEFT && ft_ismoving(env, move))
			ft_cursor_left(env);
		else if (move == MUP)
			ft_get_uhistory(env);
		else if (move == MDOWN)
			ft_get_dhistory(env);
	}
}
