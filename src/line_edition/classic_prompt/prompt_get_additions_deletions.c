/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_get_additions_deletions.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 10:31:15 by mmousson          #+#    #+#             */
/*   Updated: 2019/05/04 12:04:52 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

char	*git_diff_args[] = {"/usr/bin/git", "diff-index", "--numstat", "HEAD", NULL};

/*
**
*/

static void	parse_output(int *plus, int *minus, int fd)
{
	int		i;
	char	*line;

	*plus = 0;
	*minus = 0;
	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		i = 0;
		*plus += ft_atoi(line);
		while (ft_isdigit(*(line + i)))
			i++;
		*minus += ft_atoi(line + i);
		ft_strdel(&line);
	}
	close(fd);
}

/*
**
*/

void		get_additions_deletions(int *plus, int *minus, char **env)
{
	int		p[2];
	pid_t	pid;

	if (pipe(p) == -1)
	{
		ft_putendl_fd("Pipe Failure", STDERR_FILENO);
		return ;
	}
	if ((pid = fork()) == 0)
	{
		dup2(p[1], STDOUT_FILENO);
		close(p[1]);
		execve("/usr/bin/git", git_diff_args, env);
		exit(0);
	}
	else if (pid > 0)
	{
		wait(NULL);
		close(p[1]);
		parse_output(plus, minus, p[0]);
	}
	else
		ft_putendl_fd("Fork Failure", STDERR_FILENO);
}
