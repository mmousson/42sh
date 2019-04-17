/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 02:00:25 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/10 16:44:30 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"
#include "libft.h"

static void			ft_newline(t_env *env)
{
	int				i;

	i = 0;
	if (!env->tc->tc)
		return ;
	tputs(env->tc->mr, 1, ft_putchar);
	ft_putchar('%');
	tputs(env->tc->me, 1, ft_putchar);
	while (++i < env->cm->term_x)
		ft_putchar(' ');
	tputs(env->tc->cr, 1, ft_putchar);
	tputs(env->tc->dl, 1, ft_putchar);
}

static void			ft_setprompt(t_env *env, t_prompt prompt)
{
	ft_newline(env);
	if (!(env->line = ft_get_prompt(prompt)))
		ft_errorterm(TMALLOC, env);
	env->cm->pos = prompt;
	env->p_size = prompt;
	env->prompt = prompt;
	env->len = prompt;
}

static char			*ft_cutline(t_env *env, t_prompt prompt)
{
	char			*tmp;

	if (!(tmp = ft_strdup(env->line + prompt)))
		ft_errorterm(TMALLOC, env);
	ft_strdel(&env->line);
	env->line = tmp;
	return (tmp);
}

void				ft_term_manager(t_env *env)
{
	t_tc			*tc;
	t_cm			*cm;
	t_cpy			*cpy;
	t_mode			*mode;

	tc = (t_tc*)ft_memalloc(sizeof(t_tc));
	cm = (t_cm*)ft_memalloc(sizeof(t_cm));
	cpy = (t_cpy*)ft_memalloc(sizeof(t_cpy));
	mode = (t_mode*)ft_memalloc(sizeof(t_mode));
	if (!tc || !cm || !cpy || !mode)
		ft_errorterm(TMALLOC, env);
	env->ry = NULL;
	ft_bzero(tc, sizeof(t_tc));
	ft_bzero(cm, sizeof(t_cm));
	ft_bzero(cpy, sizeof(t_cpy));
	ft_bzero(mode, sizeof(t_mode));
	env->tc = tc;
	env->tc->tc = 1;
	env->cm = cm;
	env->cpy = cpy;
	env->mode = mode;
	env->mode->mode[0] = 1;
	ft_configterm(env);
	signal_saved(env);
}

char				*ft_get_line(t_env *env, t_prompt prompt, char *argv)
{
	int			ret;

	ret = 0;
	if (env->isatty)
		ft_switch_term(env, 0);
	env->ctrld = 0;
	env->tc->tc = 1;
	if (!ft_check_termcaps(*env->tc))
		env->tc->tc = 0;
	while (!ret)
	{
		if (env->isatty)
			ft_setprompt(env, prompt);
		ret = ft_reader(env, argv);
	}
	if (env->isatty)
	{
		ft_switch_term(env, 1);
		return (ft_cutline(env, prompt));
	}
	return (env->line);
}
