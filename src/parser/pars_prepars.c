/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_prepars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 11:04:39 by oboutrol          #+#    #+#             */
/*   Updated: 2019/07/01 12:18:19 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static int		pars_error(int type)
{
	static char	*error[NB_PR] = {
		"arg", "`;'", "red", "`|'", "space", "`\\n'", "sepa"
	};

	ft_putstr_fd("42sh: parse error near ", 2);
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
		{CHAR, SMCL, REDI, EROR, SMCL, SMCL, SMCL},
		{CHAR, EROR, EROR, EROR, REDI, EROR, EROR},
		{CHAR, EROR, REDI, EROR, PIPE, MORE, EROR}
	};

	if (old_type >= NB_TY || old_type < 0 || type >= NB_PR || type < 0)
		return (EROR);
	return (mat[old_type][type]);
}

static int		red_valid(t_tok *token)
{
	int			i;
	int			esp;
	char		red;
	char		*tmp;

	i = 0;
	esp = 0;
	if (!token || !(token->content))
		return (1);
	tmp = token->content;
	if (tmp[i] == '&')
	{
		i++;
		esp = 1;
	}
	if (!(red = tmp[i]))
		return (1);
	if (tmp[++i] == red)
		i++;
	if ((tmp[i] == '&' && !esp) || !tmp[i])
		return (0);
	ft_putstr_fd("42sh: syntax error near unexpected token `", 2);
	ft_putchar_fd(red, 2);
	ft_putstr_fd("'\n", 2);
	return (1);
}

int				pars_prepars(t_tok *token)
{
	t_tok		*tmp;
	int			type;
	int			old_type;

	old_type = SMCL;
	tmp = token;
	while (tmp)
	{
		tmp = tmp->next;
		type = ft_get_type(tmp);
		if (is_sepa_tok(tmp))
			type = SEPA;
		if (tmp && tmp->status == CH && pars_bracket(&tmp))
			return (0);
		else if (type == REDI && red_valid(tmp))
			return (0);
		old_type = ft_mat_type(old_type, type);
		if (old_type == EROR)
			return (pars_error(type));
		else if (old_type == MORE)
			return (2);
	}
	return (1);
}
