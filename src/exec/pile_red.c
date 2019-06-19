/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pile_red.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 16:13:58 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/15 11:43:18 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

static t_lstred	*new_lstred(t_dup *dup, int close)
{
	t_lstred	*new;

	if (!(new = (t_lstred*)ft_memalloc(sizeof(t_lstred))))
		return (NULL);
	new->int_og = dup->int_og;
	new->int_dir = dup->int_dir;
	new->name_og = dup->name_og;
	dup->name_og = NULL;
	new->name_dir = dup->name_dir;
	dup->name_dir = NULL;
	new->is_here = dup->is_here;
	new->simple = dup->simple;
	new->close = close;
	return (new);
}

static void		pile_last_red(t_dup *dup, t_launch *cmd, int close)
{
	t_lstred	*red;
	t_lstred	*new;

	red = cmd->lstred;
	while (red && red->next)
		red = red->next;
	new = new_lstred(dup, close);
	if (!red)
		cmd->lstred = new;
	else
		red->next = new;
}

void			pile_red(t_dup *dup, t_launch *cmd, int close)
{
	pile_last_red(dup, cmd, close);
}
