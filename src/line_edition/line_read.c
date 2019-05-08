/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 21:28:08 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/03 16:34:14 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"
#include <unistd.h>

static int			line_read_notermcaps(void)
{
	int				ret;
	char			*line;
	static char		*isread = NULL;

	if (g_env.tc->tc)
		return (0);
	if ((ret = get_line(STDIN_FILENO, &line, &isread)) > 0 && !g_env.sigc)
	{
		if (!(g_env.line = ft_strjoinf(g_env.line, line)))
			sh_errorterm(TMALLOC);
		ft_strdel(&line);
	}
	ft_strdel(&isread);
	if (ret == 0 && !g_env.sigc)
		g_env.ctrld = 1;
	return (1);
}

static int			line_read_isatty(void)
{
	char			buf[BUFF_SIZE + 1];
	int				ret;

	if (line_read_notermcaps())
		return (0);
	if ((ret = read(STDIN_FILENO, buf, sizeof(buf))) > 0 && !g_env.sigc)
	{
		buf[ret] = '\0';
		if (!line_update(buf, ret))
			return (0);
	}
	if (g_env.sigc)
		return (0);
	return (1);
}

static void			line_endofread(void)
{
	if (!g_env.tc->tc)
		return ;
	ft_putchar('\n');
	g_env.cm->tmpy = 0;
	line_reset_history();
	ft_strdel(&(g_env.oldline));
}

int					line_reader(char *argv)
{
	if (line_read_isnotatty())
		return (1);
	if (argv && line_read_isarg(argv))
		return (1);
	ft_putstr(g_env.line);
	if (g_env.tc->tc && !(g_env.oldline = ft_strdup(g_env.line)))
		sh_errorterm(TMALLOC);
	while (1)
	{
		if (!line_read_isatty())
			break ;
	}
	if (g_env.sigc)
	{
		ft_strdel(&g_env.line);
		ft_strdel(&g_env.oldline);
		g_env.sigc = 0;
		return (0);
	}
	line_endofread();
	return (1);
}
