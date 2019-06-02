/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 10:52:54 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/02 19:54:45 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

static t_lstfd	*new_fd(int fd)
{
	t_lstfd		*new;

	if (!(new = (t_lstfd*)malloc(sizeof(t_lstfd))))
		return (NULL);
	new->next = NULL;
	new->fd = fd;
	return (new);
}

static void		ft_add_fd(int fd, t_launch *cmd)
{
	t_lstfd		*lst;

	lst = cmd->lstfd;
	while (lst && lst->next)
		lst = lst->next;
	if (lst)
		lst->next = new_fd(fd);
	else
		cmd->lstfd = new_fd(fd);
}

void			ft_add_pile(int og, int dir, t_launch *cmd)
{
	ft_add_fd(dir, cmd);
	if (og == 0)
		cmd->in = dir;
	if (og == 1)
		cmd->out = dir;
	if (og == 2)
		cmd->err = dir;//origine: dup des fd 0 1 2, le rez n'a plus de sens
}

static void		ft_close_fd(t_lstfd *lst)
{
	if (!lst)
		return ;
	ft_close_fd(lst->next);
	if (lst->fd != 1 && lst->fd != 2 && lst->fd != 0)
		close(lst->fd);
}

void			ft_res_pile(t_launch *cmd)
{
	if (cmd)
	{
		if (cmd->in != -2)
		{
			dup2(cmd->in, 0);
			close(cmd->in);
		}
		if (cmd->out != -2)
		{
			dup2(cmd->out, 1);
			close(cmd->out);
		}
		if (cmd->err != -2)
		{
			dup2(cmd->err, 2);
			close(cmd->err);
		}
	}
	ft_close_fd(cmd->lstfd);
	ft_free_lstfd(cmd->lstfd);
	cmd->lstfd = NULL;
}
