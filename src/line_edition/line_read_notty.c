/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_read_notty.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 21:27:30 by roliveir          #+#    #+#             */
/*   Updated: 2019/06/11 13:53:10 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"
#include <fcntl.h>

int					line_read_isnotatty(void)
{
	int				ret;
	char			buf[BUFF_SIZE + 1];
	char			*tmp;

	if (g_env.isatty)
		return (0);
	if (!(g_env.line = ft_strnew(1)))
		sh_errorterm(TMALLOC);
	while ((ret = read(STDIN_FILENO, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (!(tmp = ft_strjoinf(g_env.line, buf)))
			sh_errorterm(TMALLOC);
		g_env.line = tmp;
	}
	return (1);
}

int					line_read_isarg(char *argv)
{
	int				fd;
	int				ret;
	char			buf[BUFF_SIZE + 1];
	char			*tmp;

	if (!(g_env.line = ft_strnew(1)))
		sh_errorterm(TMALLOC);
	if ((fd = open(argv, O_RDONLY)) < 1)
	{
		ft_putstr_fd("42sh: cannot open ", 2);
		ft_putendl_fd(argv, 2);
		sh_quiterm();
	}
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (!(tmp = ft_strjoinf(g_env.line, buf)))
			sh_errorterm(TMALLOC);
		g_env.line = tmp;
	}
	return (1);
}
