/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 12:15:16 by oboutrol          #+#    #+#             */
/*   Updated: 2019/04/07 12:06:51 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexpars.h"
#include <stdlib.h>

int				ft_do_fct(int k, t_args *arg)
{
	int			ret;
	static int	(*fct_list_unique[22])(t_args*) = {
		nothing, ft_newarg, ft_starg, ft_empargs, ft_newcmd,
		ft_pipe, ft_eperl, nothing, ft_lim, ft_quit,
		ft_redirect, ft_newred, nothing, nothing, nothing,
		nothing, nothing, nothing, nothing, ft_dbqt,
		ft_spqt, ft_more_pipe};

	if (k < 22)
		ret = (*(fct_list_unique[k]))(arg);
	else
		ret = 1;
	return (ret);
}

int				ft_error(char *str, int ret)
{
	ft_putstr_fd(str, 2);
	return (ret);
}

int				ft_pars_error(t_args *arg)
{
	ft_error("21sh: parse error\n", 2);
	ft_quit(arg);
	ft_free_arg(arg);
	return (0);
}

int				ft_lex(char **str, t_env *line, char ***arge)
{
	int			fct;
	t_args		arg;
	int			ret;

	if (!*str)
		return (0);
	arg = init_args(*str, line, arge);
	ret = 0;
	while (arg.charac != END)
	{
		arg.old_status = arg.status;
		arg.charac = ft_charac(arg.str[arg.k]);
		fct = get_fct(arg.status, arg.charac);
		arg.status = get_status(arg.status, arg.charac);
		if (arg.status == -1)
			return (ft_pars_error(&arg));
		if ((ret = ft_do_fct(fct, &arg)) < 0)
			break ;
		arg.k++;
	}
	ret = ft_pars(arg.cmd, arge, &arg, ret);
	ft_free_arg(&arg);
	return (ret);
}
