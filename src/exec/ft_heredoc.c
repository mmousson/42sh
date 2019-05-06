/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 13:15:59 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/06 22:10:03 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"
#include "libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

void		ft_launch_here(char *end, int fd)
{
	char	*line;
	int		stop;

	stop = 0;
	line = NULL;
	dup2(0, 1);
	while (!end || !stop)
	{
		line = line_get_readline(PHEREDOC, NULL);
		if (((!line || !line[0]) && g_env.ctrld) || !ft_strcmp(line, end))
			stop = 1;
		else if (end && ft_strcmp(line, end))
			ft_putendl_fd(line, fd);
		if (line)
		{
			free(line);
			line = NULL;
		}
	}
	ft_strdel(&end);
}

int			ft_heredoc(char *end, t_launch *cmd)
{
	int		fdpipe[2];
	int		success;
	int		fd;

	pipe(fdpipe);
	if (((success = fork())) == 0)
	{
		//sig_setchild(1);
		fd = dup(1);
		dup2(fdpipe[1], fd);
		close(fdpipe[0]);
		close(fdpipe[1]);
		ft_launch_here(end, fd);
		sh_quiterm();
	}
	ft_add_pile(0, 0, cmd);
	dup2(fdpipe[0], 0);
	close(fdpipe[1]);
	close(fdpipe[0]);
	wait(&success);
	return (0);
}
