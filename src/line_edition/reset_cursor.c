/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_cursor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:22:35 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/07 16:38:34 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"
#include "libft.h"

static int			ft_lenline(t_env *env, int pos)
{
	int				len;

	len = 0;
	while (ft_getx(env, pos))
	{
		pos--;
		len++;
	}
	return (len);
}

static void			ft_back_left(t_env *env, int pos)
{
	int				i;
	int				len_line;

	while (pos != env->cm->pos)
	{
		i = -1;
		if (!ft_getx(env, pos))
		{
			len_line = ft_lenline(env, pos - 1);
			tputs(env->tc->up, 1, ft_putchar);
			if (pos - len_line > env->cm->pos)
				pos -= len_line;
			else
			{
				while (++i < len_line)
					tputs(env->tc->nd, 1, ft_putchar);
			}
		}
		else
			tputs(env->tc->le, 1, ft_putchar);
		pos--;
	}
}

void				ft_reset_cursor(t_env *env)
{
	ft_back_left(env, env->len);
	if (!ft_getx(env, env->cm->pos)
			&& env->len % env->cm->term_x == 0)
	{
		tputs(env->tc->cr, 1, ft_putchar);
		tputs(env->tc->doo, 1, ft_putchar);
	}
}
