/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 01:06:53 by oboutrol          #+#    #+#             */
/*   Updated: 2019/04/01 02:51:46 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexpars.h"
#include "libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

void	ft_launch_here(t_args *args, char *end, int fd)
{
	char *line;

	line = NULL;
	while (!line || !end || ft_strcmp(line, end))
	{
		if (line)
		{
			free(line);
			line = NULL;
		}
		line = ft_get_line(args->line, PHEREDOC, NULL);
		if (ft_strcmp(line, end))
			ft_putendl_fd(line, fd);
	}
	if (line)
	{
		free(line);
		line = NULL;
	}
}

int		ft_heredoc(t_args *args, char *end)
{
	int	fdpipe[2];
	int	success;
	int	fd;

	pipe(fdpipe);
	if ((success = fork()) == 0)
	{
		fd = dup(1);
		dup2(fdpipe[1], fd);
		close(fdpipe[1]);
		close(fdpipe[0]);
		ft_launch_here(args, end, fd);
		exit(1);
	}
	dup2(fdpipe[0], 0);
	close(fdpipe[0]);
	close(fdpipe[1]);
	wait(&success);
	return (0);
}
