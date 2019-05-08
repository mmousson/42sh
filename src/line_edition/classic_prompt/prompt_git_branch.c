/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_git_branch.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 08:39:13 by mmousson          #+#    #+#             */
/*   Updated: 2019/05/06 19:55:03 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/param.h>
#include "libft.h"
#include "prompt.h"

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
**	Handles the line of the git branch infos once it has been read by the
**	'GNL' func
**
**	Return Value: The actual size-on-screen of the printed infos
*/

static int	handle_git_branch_line(int add, int del, char *l)
{
	int	ret;

	ft_putstr_fd(GIT_BRANCH_START, 1);
	ft_putstr_fd((add + del == 0) ? GIT_UP_TO_DATE : GIT_NOT_UP_TO_DATE, 1);
	ret = put_arrow(BANNER_ARROW);
	ft_putstr_fd("\033[0;38;2;0;0;0;48;2;", 1);
	ret += put_arrow((add + del) ? GIT_RED_INFOS"\xEE\x82\xA0 "
		: GIT_UP_TO_DATE"\xEE\x82\xA0 ");
	ret += write(1, ft_strrchr(l, '/') + 1, ft_strlen(ft_strrchr(l, '/') + 1));
	if (add + del == 0)
		ret += put_arrow(GIT_END_BANNER);
	else
	{
		ret += write(1, " * +", 4);
		ft_putnbr(add);
		ret += write(1, " / -", 4);
		ft_putnbr(del);
		ret += (ft_order_of_magnitude(add) + ft_order_of_magnitude(del));
		ret += put_arrow(GIT_ERR_END_BANNER);
	}
	ft_strdel(&l);
	return (ret);
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
**	Return Value: The actual size-on-screen of the printed infos
*/

static int	print_infos(char *dot_git, int add, int del)
{
	int		ret;
	int		fd;
	char	*l;
	char	*tmp;

	ret = 0;
	if ((tmp = ft_strjoin(dot_git, "/HEAD")) == NULL)
	{
		ft_putendl_fd("Internal Malloc Error", STDERR_FILENO);
		return (0);
	}
	if ((fd = open(tmp, O_RDONLY)) != -1)
	{
		if (get_next_line(fd, &l) && l != NULL)
			ret = handle_git_branch_line(add, del, l);
		ft_strdel(&dot_git);
		ft_strdel(&tmp);
		close(fd);
	}
	return (ret);
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

int			prompt_git_branch(char **env)
{
	int		ret;
	int		plus;
	int		del;
	DIR		*dir;
	char	*dot_git;

	if ((dot_git = get_dot_git_path()) == NULL
		|| (dir = opendir(dot_git)) == NULL)
	{
		ft_putstr(GIT_NO_GIT);
		return (2);
	}
	else
	{
		get_additions_deletions(&plus, &del, env);
		ret = print_infos(dot_git, plus, del);
		closedir(dir);
		return (ret);
	}
}
