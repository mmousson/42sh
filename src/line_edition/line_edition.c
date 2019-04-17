/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 22:59:54 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/10 17:16:44 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"
#include <stdlib.h>
#include "libft.h"
#include <unistd.h>
#include <sys/ioctl.h>

void				ft_update_termsize(t_env *env)
{
	struct winsize	w;

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &w) == -1)
		ft_errorterm(TIOCTL, env);
	env->cm->term_x = w.ws_col;
	env->cm->term_y = w.ws_row;
}

void				ft_clear_line(t_env *env)
{
	int				i;

	i = -1;
	while (++i < env->cm->tmpy)
		tputs(env->tc->up, 1, ft_putchar);
	tputs(env->tc->cd, 1, ft_putchar);
	tputs(env->tc->cr, 1, ft_putchar);
	tputs(env->tc->dl, 1, ft_putchar);
}

void				ft_paste(t_env *env, char *str)
{
	if (!str)
		return ;
	env->line = ft_addstr(env, str);
	ft_reset_history(env);
	ft_strdel(&env->oldline);
	if (!(env->oldline = ft_strdup(env->line)))
		ft_errorterm(TMALLOC, env);
	ft_cursor_motion(env, MRIGHT, (int)ft_strlen(str));
}

static int			ft_choose_mode(t_env *env, char *str, int ret)
{
	int				cap;
	
	if (env->mode->n_select)
		cap = ft_line_cpy(env, str, ret);
	else if (env->mode->mode[MVI])
		cap = ft_line_vi(env, str, ret);
	else if (env->mode->mode[MREADLINE])
		cap = ft_line_readline(env, str, ret);
	else
		cap = ft_line_manager(env, str, ret);
	return (cap);
}

int					ft_update_line(t_env *env, char *str, int ret)
{
	int				i;
	int				cap;

	i = -1;
	if (!str)
		return (0);
	env->len = (int)ft_strlen(env->line) + 1;
	cap = ft_choose_mode(env, str, ret);
	env->len = (int)ft_strlen(env->line);
	ft_clear_line(env);
	ft_print_line(env);
	ft_reset_cursor(env);
	env->cm->tmpy = ft_gety(env, env->cm->pos);
	return (cap);
}
