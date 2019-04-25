/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 22:59:54 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/25 09:11:57 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>

void				ft_update_termsize(void)
{
	struct winsize	w;

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &w) == -1)
		ft_errorterm(TIOCTL);
	g_env.cm->term_x = w.ws_col;
	g_env.cm->term_y = w.ws_row;
}

void				ft_clear_line(void)
{
	int				i;

	i = -1;
	while (++i < g_env.cm->tmpy)
		tputs(g_env.tc->up, 1, ft_putchar);
	tputs(g_env.tc->cd, 1, ft_putchar);
	tputs(g_env.tc->cr, 1, ft_putchar);
	tputs(g_env.tc->dl, 1, ft_putchar);
}

void				ft_paste(char *str, int count)
{
	int				tmp;

	tmp = count + 1;
	if (!str)
		return ;
	while (--tmp)
		g_env.line = ft_addstr(str);
	ft_reset_history();
	ft_strdel(&g_env.oldline);
	if (!(g_env.oldline = ft_strdup(g_env.line)))
		ft_errorterm(TMALLOC);
	ft_cursor_motion(MRIGHT, (int)ft_strlen(str) * count);
}

static int			ft_choose_mode(char *str, int ret)
{
	int				cap;
	
	if (g_env.mode->n_select)
		cap = ft_line_cpy(str, ret);
	else if (g_env.mode->mode[MVI])
		cap = ft_line_vi(str, ret);
	else
		cap = ft_line_manager(str, ret);
	return (cap);
}

int					ft_update_line(char *str, int ret)
{
	int				i;
	int				cap;

	i = -1;
	if (!str)
		return (0);
	g_env.len = (int)ft_strlen(g_env.line) + 1;
	cap = ft_choose_mode(str, ret);
	g_env.len = (int)ft_strlen(g_env.line);
	ft_clear_line();
	ft_print_line();
	ft_reset_cursor();
	g_env.cm->tmpy = ft_gety(g_env.cm->pos);
	return (cap);
}
