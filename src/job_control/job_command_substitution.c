/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_command_substitution.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 11:53:49 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/27 12:15:18 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"
#include "lex.h"
#include "sh42.h"

static char	*file_get_content(char *path)
{
	int		fd;
	char	*tmp;
	char	*tmp_buffer;
	char	*buffer;

	buffer = NULL;
	if ((fd = open(path, O_RDONLY)) != -1)
	{
		while (get_next_line(fd, &tmp) > 0)
		{
			tmp_buffer = buffer;
			buffer = ft_strjoin(buffer, tmp);
			ft_strdel(&tmp);
			ft_strdel(&tmp_buffer);
			if (buffer == NULL)
			{
				ft_putendl_fd("42sh: Internal Malloc Error", STDERR_FILENO);
				break ;
			}
		}
		close(fd);
	}
	else
		ft_putendl3_fd("42sh: opening file '", path, "' failed", STDERR_FILENO);
	return (buffer);
}

static void	setup_file_descriptors(char *path, int *bkp_out, int *bkp_err)
{
	int	file_fd;

	if ((file_fd = open(path, O_RDWR)) == -1)
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

static void	restore_file_descriptors(int bkp_out, int bkp_err)
{
	if (bkp_out != -1)
	{
		dup2(bkp_out, STDOUT_FILENO);
		close(bkp_out);
	}
	if (bkp_err != -1)
	{
		dup2(bkp_err, STDOUT_FILENO);
		close(bkp_err);
	}
}

char		*job_command_substitution(char *command, char ***env)
{
	int		bkp_out;
	int		bkp_err;
	char	*res;
	char	*tmp_file;

	bkp_out = -1;
	bkp_err = -1;
	tmp_file = utility_generate_tmp_filename();
	setup_file_descriptors(tmp_file, &bkp_out, &bkp_err);
	lex_str(&command, env);
	restore_file_descriptors(bkp_out, bkp_err);
	res = file_get_content(tmp_file);
	unlink(tmp_file);
	ft_strdel(&tmp_file);
	return (res);
}
