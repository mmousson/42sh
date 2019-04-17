/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 03:46:52 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/11 14:49:13 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"
#include "libft.h"

static int			ft_cpy_pst(t_env *env, char *str)
{
	if (ft_isaltc(str) && !env->mode->n_select)
		ft_init_cpy(env);
	else if (ft_isaltv(str) && !env->mode->n_select)
		ft_paste(env, env->cpy->str);
	else
		return (0);
	return (1);
}

int					ft_line_history(t_env *env, char *str)
{
	if (!ft_strcmp(env->tc->key[MUP], str))
		ft_cursor_motion(env, MUP, 1);
	else if (!ft_strcmp(env->tc->key[MDOWN], str))
		ft_cursor_motion(env, MDOWN, 1);
	else
		return (0);
	return (1);
}

int					ft_line_arrow(t_env *env, char *str)
{
	if (!ft_strcmp(env->tc->key[MLEFT], str))
		ft_cursor_motion(env, MLEFT, 1);
	else if (!ft_strcmp(env->tc->key[MRIGHT], str))
		ft_cursor_motion(env, MRIGHT, 1);
	else if (env->mode->mode[MNORMAL] && !ft_strcmp(str, RJUMP))
		ft_rjump(env);
	else if (env->mode->mode[MNORMAL] && !ft_strcmp(str, LJUMP))
		ft_ljump(env);
	else if (env->mode->mode[MNORMAL] && !ft_strcmp(str, UJUMP))
		ft_cursor_motion(env, MLEFT, env->cm->term_x);
	else if (env->mode->mode[MNORMAL] && !ft_strcmp(str, DJUMP))
		ft_cursor_motion(env, MRIGHT, env->cm->term_x);
	else if (env->mode->mode[MNORMAL] && !ft_strcmp(env->tc->kh, str))
		ft_home(env);
	else if (env->mode->mode[MNORMAL] && !ft_strcmp(TEND, str))
		ft_end(env);
	else
		return (0);
	return (1);
}

int					ft_line_ascii(t_env *env, char *str, int ret)
{
	if (str[0] <= 126 && str[0] >= 32)
		ft_paste(env, str);
	else if (str[0] == 127 && ret == 1)
	{
		env->line = ft_delchar(env, 1);
		env->del = 1;
		ft_cursor_motion(env, MLEFT, 1);
		env->del = 0;
	}
	else if (env->mode->mode[MNORMAL] && !ft_strcmp(env->tc->kd, str))
		env->line = ft_delchar_bs(env, 1);
	else
		return (0);
	return (1);
}

int					ft_line_manager(t_env *env, char *str, int ret)
{
	if (str[0] == '\n' && ret == 1)
		return (0);
	else if (str[0] == CTRLD && ret == 1 && env->len == env->p_size + 1)
	{
		env->ctrld = 1;
		return (0);
	}
	else if (ft_line_ascii(env, str, ret))
		return (1);
	else if (ft_line_arrow(env, str))
		return (1);
	else if (ft_cpy_pst(env, str))
		return (1);
	else if (ft_line_history(env, str))
		return (1);
	else if (ft_vi(env, str))
		return (1);
	else if (ft_read_line(env, str))
		return (1);
	return (1);
}
