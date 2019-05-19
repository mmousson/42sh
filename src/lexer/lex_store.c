/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_store.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 11:51:09 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/19 18:40:57 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include <stdlib.h>

#include "libft.h"

int			lex_last_pile(t_stat *stat)
{
	t_st	*tmp;

	tmp = stat->stack;
	if (!tmp)
		return (CHA);
	while (tmp && tmp->next)
		tmp = tmp->next;
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
	tmp = stat->stack;
	if (!(stat->stack))
	{
		stat->status = EP;
		return (-1);
	}
	while (tmp && tmp->next)
		tmp = tmp->next;
	if ((tmp->elmt == PAO || tmp->elmt == DOL) && new_elmt == PAC)
		pop_last_stack(stat);
	else if ((tmp->elmt == SQT || tmp->elmt == DQT) && new_elmt == tmp->elmt)
		pop_last_stack(stat);
	else
	{
		stat->status = EP;
		return (-1);//error personalised avec tmp->elmt
	}
	stat->status = lex_last_pile(stat);
	lex_add_char(buff, &(stat->load), stat->cha);
	return (0);
}

int			lex_pile_up(t_stat *stat, char buff[BUF])
{
	t_st	*tmp;
	int		new_stat;

	new_stat = lex_get_ch(stat->cha);
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
		if (lex_pile_up(stat, buff))//pile up if last != current
			return (1);//error case if 
	}
	else if (stat->status == US)
		if (lex_pile_down(stat, buff))//pile down if last != current
			return (1);
	stat->status = lex_last_pile(stat);// return last type enconter in pile
	ft_putstr("current pile: ");
	lex_print_stack(stat->stack);
	ft_putchar('\n');
	return (0);
}
