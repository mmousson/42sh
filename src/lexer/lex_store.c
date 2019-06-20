/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_store.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 11:51:09 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/20 11:47:55 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

int			lex_last_pile(t_stat *stat)
{
	t_st	*tmp;

	tmp = stat->stack;
	if (!tmp)
		return (CHA);
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp->elmt == CBO)
		return (PAO);
	return (tmp->elmt);
}

void		pop_last_stack(t_stat *stat)
{
	t_st	*tmp;

	tmp = stat->stack;
	if (!tmp)
		return ;
	if (!tmp->next)
	{
		free(tmp);
		stat->stack = NULL;
	}
	else
	{
		while (tmp && tmp->next && tmp->next->next)
			tmp = tmp->next;
		free(tmp->next);
		tmp->next = NULL;
	}
}

int			lex_pile_down(t_stat *stat, char buff[BUF])
{
	t_st	*tmp;
	int		new_elmt;

	new_elmt = lex_get_ch(stat->cha);
	if (stat->cha == '}')
		new_elmt = CBC;
	tmp = stat->stack;
	if (!(stat->stack))
		return (error_ep_or_ec(stat->cha, stat));
	while (tmp && tmp->next)
		tmp = tmp->next;
	if ((tmp->elmt == PAO || tmp->elmt == DOL) && new_elmt == PAC)
		pop_last_stack(stat);
	else if (tmp->elmt == CBO && new_elmt == CBC)
		pop_last_stack(stat);
	else if ((tmp->elmt == SQT || tmp->elmt == DQT) && new_elmt == tmp->elmt)
		pop_last_stack(stat);
	else
		return (error_ep_or_ec(stat->cha, stat));
	stat->status = lex_last_pile(stat);
	lex_add_char(buff, &(stat->load), stat->cha);
	return (0);
}

int			lex_pile_up(t_stat *stat, char buff[BUF])
{
	t_st	*tmp;
	int		new_stat;

	new_stat = lex_get_ch(stat->cha);
	if (stat->cha == '{')
		new_stat = CBO;
	tmp = stat->stack;
	if (!(stat->stack))
		stat->stack = init_pile(new_stat);
	else
	{
		while (tmp && tmp->next)
			tmp = tmp->next;
		if ((new_stat == DQT || new_stat == SQT)
				&& new_stat == tmp->elmt)
			lex_pile_down(stat, buff);
		else
			tmp->next = init_pile(new_stat);
	}
	stat->status = lex_last_pile(stat);
	lex_add_char(buff, &(stat->load), stat->cha);
	return (0);
}

int			lex_store(t_stat *stat, char buff[BUF])
{
	if (stat->status == SK)
	{
		if (lex_pile_up(stat, buff))
			return (1);
	}
	else if (stat->status == US)
		if (lex_pile_down(stat, buff))
			return (1);
	stat->status = lex_last_pile(stat);
	return (0);
}
