/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_read_notty.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 21:27:30 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/06 21:36:02 by roliveir         ###   ########.fr       */
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
		ft_printf("21sh: cannot open %s\n", argv);
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
