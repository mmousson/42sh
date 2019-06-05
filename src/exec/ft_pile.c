/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 10:52:54 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/05 03:55:47 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

static t_lstfd	*new_fd(int dir, int og, int close)
{
	t_lstfd		*new;

	if (!(new = (t_lstfd*)malloc(sizeof(t_lstfd))))
		return (NULL);
	new->next = NULL;
	new->dir = dir;
	new->og = og;
	new->close = close;
	return (new);
}

static void		ft_add_fd(int dir, int og, int close, t_launch *cmd)
{
	t_lstfd		*lst;

	lst = cmd->lstfd;
	while (lst && lst->next)
		lst = lst->next;
	if (lst)
		lst->next = new_fd(dir, og, close);
	else
		cmd->lstfd = new_fd(dir, og, close);
}

void			ft_add_pile(int og, int dir, t_launch *cmd, int close)
{
	ft_add_fd(dir, og, close, cmd);
	if (og == 0)
		cmd->in = dir;
	if (og == 1)
		cmd->out = dir;
	if (og == 2)
		cmd->err = dir;//origine: dup des fd 0 1 2, le rez n'a plus de sens
}
