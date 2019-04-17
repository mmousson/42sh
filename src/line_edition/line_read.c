/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 21:28:08 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/07 16:22:13 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "line_edition.h"
#include <unistd.h>

static int			ft_read_notermcaps(t_env *env)
{
	int				ret;
	char			*line;
	static char		*isread = NULL;

	if (env->tc->tc)
		return (0);
	if ((ret = get_line(STDIN_FILENO, &line, &isread)) > 0 && !env->sigc)
	{
		if (!(env->line = ft_strjoinf(env->line, line)))
			ft_errorterm(TMALLOC, env);
		ft_strdel(&line);
	}
	ft_strdel(&isread);
	if (ret == 0 && !env->sigc)
		env->ctrld = 1;
	return (1);
}

static int			ft_read_isatty(t_env *env)
{
	char			buf[BUFF_SIZE + 1];
	int				ret;

	if (ft_read_notermcaps(env))
		return (0);
	if ((ret = read(STDIN_FILENO, buf, sizeof(buf))) > 0 && !env->sigc)
	{
		buf[ret] = '\0';
		if (!ft_update_line(env, buf, ret))
			return (0);
	}
	if (env->sigc)
		return (0);
	return (1);
}

static void			ft_endofread(t_env *env)
{
	if (!env->tc->tc)
		return ;
	ft_putchar('\n');
	env->cm->tmpy = 0;
	ft_reset_history(env);
	ft_strdel(&(env->oldline));
}

int					ft_reader(t_env *env, char *argv)
{
	if (ft_read_isnotatty(env))
		return (1);
	if (argv && ft_read_isarg(env, argv))
		return (1);
	ft_putstr(env->line);
	if (env->tc->tc && !(env->oldline = ft_strdup(env->line)))
		ft_errorterm(TMALLOC, env);
	while (1)
	{
		if (!ft_read_isatty(env))
			break ;
	}
	if (env->sigc)
	{
		env->sigc = 0;
		return (0);
	}
	ft_endofread(env);
	return (1);
}
