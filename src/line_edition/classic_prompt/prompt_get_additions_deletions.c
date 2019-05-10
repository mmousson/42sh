/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_get_additions_deletions.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 10:31:15 by mmousson          #+#    #+#             */
/*   Updated: 2019/05/08 19:56:59 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __linux__

# include <sys/wait.h>
#endif

#include <unistd.h>
#include "libft.h"

/*
**	Program name (path) and arguments to the binary giving us the
**	wanted details
*/

char	*g_git_diff_args[] = {
	"/usr/bin/git",
	"diff-index",
	"--numstat",
	"HEAD",
	NULL
};

/*
**	Parse the number of additions and deletions in each line contained
**	in 'fd' (the reading end of the pipe)
**	The lines are formatted that way:
**	%d		%d		%s\n, additons, deletions, file
**
**	Arguments:
**	plus -> A pointer to an int where we will store the number of
**		additions in the repository
**	minus -> A pointer to an int where we will store the number of
**		deletions in the repository
**	fd -> File descriptor pointing to the reading of the pipe
**
**	Return Value: NONE
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
		if (line != NULL)
		{
			i = 0;
			*plus += ft_atoi(line);
			while (*(line + i) != '\0' && ft_isdigit(*(line + i)))
				i++;
			*minus += ft_atoi(line + i);
			ft_strdel(&line);
		}
	}
	close(fd);
}

/*
**	This function will the total amount of additions and deletions in the
**	current git repository, if any
**	Note that this function will not be called if the current path is not
**	in a valid git repository
**	The informations will retrieved using the binary 'git' located in
**	'/usr/bin/git' with the arguments and options defined in the global
**	variable 'g_git_diff_args' defined above
**	So we first fork the program, make the child launch the command and write
**	its result in the Writing end of a pipe
**	The parent waits fot the child to complete and then reads the result
**	in the reading end of the pipe and parses it with the function
**	'parse_output' defined above
**
**	Arguments:
**	plus -> A pointer to an int where we will store the number of
**		additions in the repository
**	minus -> A pointer to an int where we will store the number of
**		deletions in the repository
**	env -> A definiton of the shell's current environment
**
**	Return Value: NONE
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
		execve("/usr/bin/git", g_git_diff_args, env);
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
