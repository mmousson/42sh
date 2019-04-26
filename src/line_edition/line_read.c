/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 21:28:08 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/26 13:16:11 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"
#include <unistd.h>

static int			ft_read_notermcaps(void)
{
	int				ret;
	char			*line;
	static char		*isread = NULL;

	if (g_env.tc->tc)
		return (0);
	if ((ret = get_line(STDIN_FILENO, &line, &isread)) > 0 && !g_env.sigc)
	{
		if (!(g_env.line = ft_strjoinf(g_env.line, line)))
			ft_errorterm(TMALLOC);
		ft_strdel(&line);
	}
	ft_strdel(&isread);
	if (ret == 0 && !g_env.sigc)
		g_env.ctrld = 1;
	return (1);
}

static int			ft_read_isatty(void)
{
	char			buf[BUFF_SIZE + 1];
	int				ret;

	if (ft_read_notermcaps())
		return (0);
	if ((ret = read(STDIN_FILENO, buf, sizeof(buf))) > 0 && !g_env.sigc)
	{
		buf[ret] = '\0';
		if (!ft_update_line(buf, ret))
			return (0);
	}
	if (g_env.sigc)
		return (0);
	return (1);
}

static void			ft_endofread(void)
{
	if (!g_env.tc->tc)
		return ;
	ft_putchar('\n');
	g_env.cm->tmpy = 0;
	ft_reset_history();
	ft_strdel(&(g_env.oldline));
}

int					ft_reader(char *argv)
{
	if (ft_read_isnotatty())
		return (1);
	if (argv && ft_read_isarg(argv))
		return (1);
	ft_putstr(g_env.line);
	if (g_env.tc->tc && !(g_env.oldline = ft_strdup(g_env.line)))
		ft_errorterm(TMALLOC);
	while (1)
	{
		if (!ft_read_isatty())
			break ;
	}
	if (g_env.sigc)
	{
		g_env.sigc = 0;
		return (0);
	}
	ft_endofread();
	return (1);
}
