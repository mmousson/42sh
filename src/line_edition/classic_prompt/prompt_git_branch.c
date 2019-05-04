/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_git_branch.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 08:39:13 by mmousson          #+#    #+#             */
/*   Updated: 2019/05/04 11:12:00 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/param.h>
#include "line_edition.h"

/*
**	This function recursively searches in the current directory, and the parent
**	and the parent of parent, etc... for a directory named ".git" which would
**	tell us that we are in a git repository
**
**	Arguments: NONE
**
**	Return Value:
**	NULL -> We are not in a git repository
**	NON_NULL -> We are in a git repository and the path to the '.git' folder is
**		returned
*/

static char	*get_dot_git_path(void)
{
	char	*tmp;
	char	result[MAXPATHLEN + 1];

	if (getcwd(result, MAXPATHLEN + 1) == NULL)
		return (NULL);
	while (ft_strlen(result) != 0)
	{
		tmp = ft_strjoin(result, "/.git");
		if (access(tmp, F_OK) != -1)
			return (tmp);
		else
		{
			ft_strdel(&tmp);
			if ((tmp = ft_strrchr(result, '/')) != NULL)
				tmp[0] = '\0';
			else
				return (NULL);
		}
	}
	return (NULL);
}

/*
**	This function formats informations about the current git branch
**	Currently, only the branch name is displayed
**
**	Arguments:
**	e -> Boolean value telling us whether the last command reulted in an error
**	add -> How much we must add to the number of printed characters in the
**		prompt, returned by the function 'line_write_prompt' defined in
**		line_edition/prompt_classic.c
**	dot_git -> The path to the repository's '.git' folder
**
**	Return Value: NONE
*/

static void	print_infos(int e, char *dot_git, int add, int del)
{
	int		fd;
	char	*l;
	char	*tmp;

	if ((tmp = ft_strjoin(dot_git, "/HEAD")) == NULL)
	{
		ft_putendl_fd("Internal Malloc Error", STDERR_FILENO);
		return ;
	}
	if ((fd = open(tmp, O_RDONLY)) != -1)
	{
		if (get_next_line(fd, &l) && l != NULL)
		{
			ft_putstr("\033[0;38;2;50;50;50;48;2;");
			ft_putstr((add + del == 0) ? "50;200;50m" : "209;8;28m");
			ft_putstr("\xEE\x82\xB0\033[0;38;2;0;0;0;48;2;");
			ft_putstr((add + del == 0) ? "50;200;50m \xEE\x82\xA0 "
				: "209;8;28;38;2;255;255;255m \xEE\x82\xA0 ");
			ft_putstr(ft_strrchr(l, '/') + 1);
			if (add + del == 0)
				ft_putstr(" \033[38;2;0;200;0;49m\xEE\x82\xB0""\033[37m");
			else
			{
				ft_putstr(" * +");
				ft_putnbr(add);
				ft_putstr(" / -");
				ft_putnbr(del);
				ft_putstr(" \033[0;38;2;209;8;28m\xEE\x82\xB0""\033[37m");
			}
			ft_strdel(&l);
		}
		ft_strdel(&dot_git);
		ft_strdel(&tmp);
		close(fd);
	}
}

/*
**	Wrapper function to format all informations and the right colors about the
**	current git branch
**
**	Arguments:
**	e -> Boolean value telling us whether the last command reulted in an error
**	add -> How much we must add to the number of printed characters in the
**		prompt, returned by the function 'line_write_prompt' defined in
**		line_edition/prompt_classic.c
**
**	Return Value: NONE
*/

void		prompt_git_branch(int e, char **env)
{
	int		plus;
	int		del;
	DIR		*dir;
	char	*dot_git;

	if ((dot_git = get_dot_git_path()) == NULL)
		return ;
	if ((dir = opendir(dot_git)) != NULL)
	{
		get_additions_deletions(&plus, &del, env);
		print_infos(e, dot_git, plus, del);
		closedir(dir);
	}
	else
	{
		ft_putstr("\033[0;38;2;50;50;50m");
		ft_putstr("\xEE\x82\xB0");
	}
}
