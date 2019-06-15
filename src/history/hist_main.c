/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 13:27:51 by roliveir          #+#    #+#             */
/*   Updated: 2019/06/15 12:05:42 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"
#include "sh42.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

static void		hist_readfile(char **line, char **isread, int fd)
{
	char		*new_line;

	while (get_next_line(fd, line) > 0)
	{
		if ((new_line = hist_parsline(*line)))
			hist_add(new_line, 0);
		ft_strdel(line);
		ft_strdel(&new_line);
	}
	ft_strdel(isread);
	close(fd);
}

static char		*hist_getpath(void)
{
	char		*path;

	if (!(path = getenv("HOME")))
		return (NULL);
	if (!(path = ft_strjoin(path, HIST_FILE)))
		sh_errorterm(TMALLOC);
	return (path);
}

void			hist_init(void)
{
	int			fd;
	char		*line;
	char		*isread;
	char		*path;

	isread = NULL;
	line = NULL;
	if (!(path = hist_getpath()))
		return ;
	fd = open(path, O_CREAT | O_RDONLY, 0644);
	ft_strdel(&path);
	if (fd == -1)
	{
		ft_putstr_fd("42sh: fail to access history\n", STDERR_FILENO);
		return ;
	}
	hist_readfile(&line, &isread, fd);
	return ;
}

static void		hist_w_infile(int fd, t_history *ry)
{
	if (ry->next)
		hist_w_infile(fd, ry->next);
	if (ry->line)
	{
		ft_putstr_fd(": ", fd);
		ft_putnbr_fd((int)ft_strlen(ry->line), fd);
		ft_putstr_fd(":0;", fd);
		ft_putendl_fd(ry->line, fd);
	}
}

void			hist_update(char *line, int stock)
{
	int			fd;
	char		*path;

	if (!(path = hist_getpath()))
		return ;
	fd = open(path, O_CREAT | O_RDWR | O_TRUNC, 0644);
	ft_strdel(&path);
	hist_add(line, stock);
	if (fd == -1)
		return ;
	hist_w_infile(fd, g_env.ry);
	close(fd);
}
