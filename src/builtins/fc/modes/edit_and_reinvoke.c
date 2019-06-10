/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_and_reinvoke.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:26:52 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/04 17:26:52 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <fcntl.h>
#include "fc.h"
#include "lex.h"
#include "sh42.h"

/*
**
*/

static int	put_commands_to_file(t_options_infos *inf, char *filename)
{
	int			fd;
	t_history	*current;
	t_history	*target;

	if ((fd = open(filename, O_RDWR | O_CREAT, 0644)) != -1)
	{
		current = inf->reversed ? inf->to : inf->from;
		target = inf->reversed ? inf->from : inf->to;
		while (current != NULL)
		{
			ft_putendl_fd(current->line, fd);
			if (current == target)
				break;
			current = current->next;
		}
		close(fd);
		return (0);
	}
	ft_putendl_fd("42sh: fc: Failed to create temporary file", STDERR_FILENO);
	return (-1);
}

/*
**
*/

static int	launch_editor(char *path, char *filename, char **env)
{
	pid_t	pid;
	char	*args[3];

	if ((pid = fork()) == 0)
	{
		args[0] = path;
		args[1] = filename;
		args[2] = NULL;
		execve(path, args, env);
	}
	else if (pid > 0)
	{
		wait(NULL);
	}
	else
	{
		ft_putendl_fd("42sh: fc: fork failed", STDERR_FILENO);
		return (-1);
	}
	return (0);
}

static int	launch_commands(char *filename, char ***env)
{
	int		ret;
	int		fd;
	char	*line;

	if ((fd = open(filename, O_RDONLY)) == -1)
	{
		ft_putstr_fd("42sh: fc: Failed to open file '", STDERR_FILENO);
		ft_putstr_fd(filename, STDERR_FILENO);
		ft_putendl_fd("' in reading mode", STDERR_FILENO);
		return (-1);
	}
	while (get_next_line(fd, &line) > 0)
	{
		ft_putendl_fd(line,2);
		ret = !lex_str(&line, env);
		ft_strdel(&line);
	}
	close(fd);
	return (ret);
}

/*
**
*/

int			blt_fc_edit_and_reinvoke(t_options_infos *inf, char ***env)
{
	int		fd;
	char	*filename;

	if ((filename = utility_generate_tmp_filename()) == NULL)
	{
		ft_putendl_fd("42sh: Internal Malloc Error", STDERR_FILENO);
		return (2);
	}
	ft_putendl_fd(filename, 2);
	if ((fd = put_commands_to_file(inf, filename)) == -1)
		return (2);
	launch_editor(inf->editor_name, filename, *env);
	launch_commands(filename, env);
	unlink(filename);
	ft_strdel(&filename);
	return (0);
}
