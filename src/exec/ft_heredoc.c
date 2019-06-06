/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 01:06:53 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/06 03:31:03 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"
#include "libft.h"
#include "expand.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

static int	is_end_esc(char *str)
{
	int		k;

	if (!str)
		return (0);
	k = -1;
	while (str[++k])
		if (ft_strchr("'\"\\", str[k]))
			return (1);
	return (0);
}

static void	ft_launch_here(char *end, int fd, int exp, char ***arge)
{
	char	*line;
	int		stop;

	stop = 0;
	line = NULL;
	while ((!line || !end || ft_strcmp(line, end)) && !stop && g_env.isatty)
	{
		if (line)
		{
			free(line);
			line = NULL;
		}
		line = line_get_readline(PHEREDOC, NULL);
		if (exp)
			expand_manager(&line, arge, NULL);
		if ((!line || !line[0]) && g_env.ctrld)
			stop = 1;
		else if (ft_strcmp(line, end))
			ft_putendl_fd(line, fd);
	}
	if (line)
	{
		free(line);
		line = NULL;
	}
}

int			ft_heredoc(char *end, char ***arge)
{
	int		fd;
	int		exp;

	if ((fd = open(".tmp_here", O_WRONLY | O_TRUNC | O_CREAT,
					S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR)) == -1)
		return (error_open("tmp file for heredoc"));
	exp = is_end_esc(end);
	expand_quote_removal(&end);
	ft_launch_here(end, fd, !exp, arge);
	close(fd);
	return (0);
}

int			ft_heredoc_read(int *og, int *dir)
{
	if ((*dir = open(".tmp_here", O_RDONLY)) == -1)
		return (error_open("tmp file for heredoc"));
	*og = 0;
	return (0);
}
/*
int			heredoc_store(t_red *red)
{
	t_red	*tmp;

	tmp = red;
	while (tmp)
	{
		if (tmp->type == REL + 20 && tmp->end_nm)
			if (ft_heredoc(tmp->end_nm))
				return (1);
		tmp = tmp->next;
	}
	return (0);
}*/
