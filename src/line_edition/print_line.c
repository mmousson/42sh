/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 03:17:58 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/10 17:17:29 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"
#include "libft.h"

static void			ft_dispatcher(t_env *env, int last_pos)
{
	int				i;

	i = 0;
	while (i < env->cm->pos && i < last_pos)
	{
		ft_putchar(env->line[i]);
		i++;
	}
	tputs(env->tc->mr, 1, ft_putchar);
	while (i < env->cm->pos || i < last_pos)
	{
		ft_putchar(env->line[i]);
		i++;
	}
	tputs(env->tc->me, 1, ft_putchar);
	if (env->line[i])
		ft_putstr(&(env->line[i]));
}

void				ft_print_line(t_env *env)
{
	if (!env->mode->n_select || env->cm->pos == env->cpy->pos)
		ft_putstr(env->line);
	else
		ft_dispatcher(env, env->cpy->pos);
	if (env->len % env->cm->term_x == 0
			&& env->cm->pos % env->cm->term_x != 0)
	{
		tputs(env->tc->cr, 1, ft_putchar);
		tputs(env->tc->doo, 1, ft_putchar);
	}
}
