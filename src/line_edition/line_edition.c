/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 22:59:54 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/19 09:23:24 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <term.h>

void				line_update_termsize(void)
{
	struct winsize	w;

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &w) == -1)
		sh_errorterm(TIOCTL);
	g_env.cm->term_x = w.ws_col;
	g_env.cm->term_y = w.ws_row;
}

void				line_clear(void)
{
	if (g_env.cm->tmpy > 0)
		tputs(tparm(g_env.tc->upm, g_env.cm->tmpy), 1, ft_putchar);
	tputs(g_env.tc->cd, 1, ft_putchar);
	tputs(g_env.tc->cr, 1, ft_putchar);
	tputs(g_env.tc->dl, 1, ft_putchar);
}

void				line_paste(char *str, int count)
{
	int				tmp;

	tmp = count + 1;
	if (!str)
		return ;
	while (--tmp)
		g_env.line = line_addstr(str);
	line_reset_history();
	ft_strdel(&g_env.oldline);
	if (!(g_env.oldline = ft_strdup(g_env.line)))
		sh_errorterm(TMALLOC);
	line_cursor_motion(MRIGHT, (int)ft_strlen(str) * count);
	g_env.k_index = 0;
}

static int			line_choose_mode(char *str, int ret)
{
	int				cap;

	if (g_env.mode->n_select)
		cap = line_cpy(str, ret);
	else if (g_env.mode->mode[MVI])
		cap = line_vi(str, ret);
	else
		cap = line_manager(str, ret);
	return (cap);
}

int					line_update(char *str, int ret)
{
	int				cap;

	if (!str)
		return (0);
	if (g_data.status == 2 && str[0] != '\t' && str[0] != '\n')
	{
		auto_free();
		ft_bzero(&g_data, sizeof(t_autodata));
	}
	vi_init_undo();
	g_env.len = (int)ft_strlen(g_env.line) + 1;
	cap = line_choose_mode(str, ret);
	g_env.len = (int)ft_strlen(g_env.line);
	line_clear();
	line_print();
	line_reset_cursor();
	g_env.cm->tmpy = line_gety(g_env.cm->pos);
	return (cap);
}
