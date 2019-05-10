/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_prepars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 11:04:39 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/10 12:30:04 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"
#include "libft.h"

int				ft_get_type(t_tok *token)
{
	int			stat;
	static int	mat_type[NB_CH] = {
		EROR, CHAR, CHAR, SPAC, REDI, REDI, CHAR, CHAR, CHAR, CHAR,
		CHAR, CHAR, PIPE, SMCL, CHAR, CHAR, CHAR, CHAR, CHAR
	};

	if (!token)
		return (ENDT);
	stat = token->status;
	if (stat >= NB_CH || stat < 0)
		return (EROR);
	return (mat_type[stat]);
}

static int		pars_error(int type)
{
	static char	*error[NB_PR] = {"arg", "`;'", "red", "`|'", "space", "`\\n'"};

	ft_putstr_fd("21sh: parse error near ", 2);
	if (type > 0 || type < NB_PR)
		ft_putstr_fd(error[type], 2);
	else
	{
		ft_putstr_fd("type ", 2);
		ft_putnbr_fd(type, 2);
	}
	ft_putstr_fd("\n", 2);
	return (0);
}

static int		ft_mat_type(int old_type, int type)
{
	static int	mat[NB_TY][NB_PR] = {
		{CHAR, SMCL, REDI, PIPE, CHAR, SMCL, SMCL},
		{CHAR, SMCL, EROR, EROR, SMCL, SMCL, EROR},
		{CHAR, EROR, EROR, EROR, REDI, EROR, EROR},
		{CHAR, EROR, EROR, EROR, PIPE, MORE, EROR}
	};

	if (old_type >= NB_TY || old_type < 0 || type >= NB_PR || type < 0)
		return (EROR);
	return (mat[old_type][type]);
}

static int		amb_red(int pipe, t_tok *tmp)
{
	if (pipe && tmp && tmp->content && !ft_strcmp(tmp->content, "<<"))
	{
		ft_putstr_fd("Ambiguous input redirect.\n", 2);
		return (1);
	}
	return (0);
}

int				pars_prepars(t_tok *token)
{
	t_tok		*tmp;
	int			type;
	int			old_type;
	int			pipe;

	pipe = 0;
	old_type = SMCL;
	tmp = token;
	while (tmp)
	{
		tmp = tmp->next;
		type = ft_get_type(tmp);
		if (is_sepa_tok(tmp))
			type = SEPA;
		if (type == PIPE)
			pipe = 1;
		else if (tmp && is_sep(tmp->status))
			pipe = 0;
		else if (tmp && tmp->status == PAC)
			expand_arith(&tmp);
		else if (type == REDI && amb_red(pipe, tmp))
			return (0);
		old_type = ft_mat_type(old_type, type);
		if (old_type == EROR)
			return (pars_error(type));
		else if (old_type == MORE)
			return (2);
	}
	return (1);
}
