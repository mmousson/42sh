/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_command_substitution.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 11:53:49 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/27 13:52:23 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"
#include "lex.h"
#include "sh42.h"

static void	update_buffer(char **buffer, char *tmp)
{
	char	*tmp_buffer;

	tmp_buffer = *buffer;
	*buffer = ft_strjoin(*buffer, tmp);
	ft_strdel(&tmp);
	ft_strdel(&tmp_buffer);
	if (buffer == NULL)
	{
		ft_putendl_fd("42sh: 1 Internal Malloc Error", STDERR_FILENO);
		return ;
	}
	tmp_buffer = *buffer;
	*buffer = ft_strjoin(*buffer, "\n");
	ft_strdel(&tmp);
	ft_strdel(&tmp_buffer);
	if (buffer == NULL)
		ft_putendl_fd("42sh: 1 Internal Malloc Error", STDERR_FILENO);
}

static char	*file_get_content(char *path)
{
	int		fd;
	char	*tmp;
	char	*buffer;

	buffer = ft_strnew(1);
	if ((fd = open(path, O_RDONLY)) != -1)
	{
		while (get_next_line(fd, &tmp) > 0)
		{
			update_buffer(&buffer, tmp);
			if (buffer == NULL)
				break ;
		}
		close(fd);
	}
	else
		ft_putendl3_fd("42sh: opening file '", path, "' failed", STDERR_FILENO);
	return (buffer);
}

static void	fds_setup_and_restore(char *path, int *bkp_out, int *bkp_err,
	int save_or_restore)
{
	int	file_fd;

	if (save_or_restore == SETUP)
	{
		if ((file_fd = open(path, O_RDWR | O_CREAT, 0644)) == -1)
		{
			ft_putendl3_fd("42sh: opening file ", path, " failed", STDERR_FILENO);
			return ;
		}
		*bkp_out = dup(STDOUT_FILENO);
		*bkp_err = dup(STDERR_FILENO);
		dup2(file_fd, STDOUT_FILENO);
		close(file_fd);
		close(STDERR_FILENO);
	}
	else
	{
		dup2(*bkp_out, STDOUT_FILENO);
		close(*bkp_out);
		dup2(*bkp_err, STDERR_FILENO);
		close(*bkp_err);
	}
}

static int	get_actual_command(char **command)
{
	size_t	new_len;
	char	*result;

	new_len = ft_strlen(*command + 2) - 1;
	if ((result = ft_strnew(new_len)) == NULL)
	{
		ft_putendl_fd("42sh: Internal Malloc Error", STDERR_FILENO);
		return (0);
	}
	ft_strncpy(result, *command + 2, new_len);
	ft_strdel(command);
	*command = result;
	return (1);
}

int			job_command_substitution(char **command, char ***env)
{
	int		bkp_out;
	int		bkp_err;
	char	*res;
	char	*tmp_file;

	if (ft_strnequ(*command, "$(", 2) && ft_strendswith(*command, ")"))
	{
		bkp_out = -1;
		bkp_err = -1;
		tmp_file = utility_generate_tmp_filename();
		fds_setup_and_restore(tmp_file, &bkp_out, &bkp_err, SETUP);
		if (!get_actual_command(command))
			return (0);
		lex_str(command, env);
		fds_setup_and_restore(tmp_file, &bkp_out, &bkp_err, RESTORE);
		res = file_get_content(tmp_file);
		*command = res;
		unlink(tmp_file);
		ft_strdel(&tmp_file);
		return (1);
	}
	else
		return (0);
}
