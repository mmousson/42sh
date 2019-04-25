/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 02:00:25 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/25 10:45:54 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

static void			ft_newline(void)
{
	int				i;

	i = 0;
	if (!g_env.tc->tc)
		return ;
	tputs(g_env.tc->mr, 1, ft_putchar);
	ft_putchar('%');
	tputs(g_env.tc->me, 1, ft_putchar);
	while (++i < g_env.cm->term_x)
		ft_putchar(' ');
	tputs(g_env.tc->cr, 1, ft_putchar);
	tputs(g_env.tc->dl, 1, ft_putchar);
}

static void			ft_setprompt(t_prompt prompt)
{
	ft_newline();
	if (!(g_env.line = ft_get_prompt(prompt)))
		ft_errorterm(TMALLOC);
	g_env.cm->pos = prompt;
	g_env.p_size = prompt;
	g_env.prompt = prompt;
	g_env.len = prompt;
}

static char			*ft_cutline(t_prompt prompt)
{
	char			*tmp;

	if (!(tmp = ft_strdup(g_env.line + prompt)))
		ft_errorterm(TMALLOC);
	ft_strdel(&g_env.line);
	g_env.line = tmp;
	return (tmp);
}

void				ft_term_manager(void)
{
	t_tc			*tc;
	t_cm			*cm;
	t_cpy			*cpy;
	t_mode			*mode;

	tc = (t_tc*)ft_memalloc(sizeof(t_tc));
	cm = (t_cm*)ft_memalloc(sizeof(t_cm));
	cpy = (t_cpy*)ft_memalloc(sizeof(t_cpy));
	mode = (t_mode*)ft_memalloc(sizeof(t_mode));
	if (!tc || !cm || !cpy || !mode)
		ft_errorterm(TMALLOC);
	g_env.ry = NULL;
	ft_bzero(tc, sizeof(t_tc));
	ft_bzero(cm, sizeof(t_cm));
	ft_bzero(cpy, sizeof(t_cpy));
	ft_bzero(mode, sizeof(t_mode));
	g_env.tc = tc;
	g_env.tc->tc = 1;
	g_env.cm = cm;
	g_env.cpy = cpy;
	g_env.mode = mode;
	g_env.mode->mode[0] = 1;
	ft_configterm();
}

char				*ft_get_line(t_prompt prompt, char *argv)
{
	int			ret;

	ret = 0;
	if (g_env.isatty)
		ft_switch_term(0);
	g_env.ctrld = 0;
	g_env.tc->tc = 1;
	if (!ft_check_termcaps(*g_env.tc))
		g_env.tc->tc = 0;
	while (!ret)
	{
		if (g_env.isatty)
			ft_setprompt(prompt);
		ret = ft_reader(argv);
	}
	if (g_env.isatty)
	{
		ft_switch_term(1);
		return (ft_cutline(prompt));
	}
	return (g_env.line);
}
