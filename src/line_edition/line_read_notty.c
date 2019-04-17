/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_read_notty.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 21:27:30 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/18 00:06:58 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"
#include "libft.h"
#include <unistd.h>
#include "printf.h"
#include <fcntl.h>

int					ft_read_isnotatty(t_env *env)
{
	int				ret;
	char			buf[BUFF_SIZE + 1];
	char			*tmp;

	if (env->isatty)
		return (0);
	if (!(env->line = ft_strnew(1)))
		ft_errorterm(TMALLOC, env);
	while ((ret = read(STDIN_FILENO, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (!(tmp = ft_strjoinf(env->line, buf)))
			ft_errorterm(TMALLOC, env);
		env->line = tmp;
	}
	return (1);
}

int					ft_read_isarg(t_env *env, char *argv)
{
	int				fd;
	int				ret;
	char			buf[BUFF_SIZE + 1];
	char			*tmp;

	env->isatty = 0;
	if (!(env->line = ft_strnew(1)))
		ft_errorterm(TMALLOC, env);
	if ((fd = open(argv, O_RDONLY)) < 1)
	{
		ft_putstr_fd("42sh: Could not open: ", STDERR_FILENO);
		ft_putendl_fd(argv, STDERR_FILENO);
		ft_quiterm(env);
	}
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (!(tmp = ft_strjoinf(env->line, buf)))
			ft_errorterm(TMALLOC, env);
		env->line = tmp;
	}
	return (1);
}
