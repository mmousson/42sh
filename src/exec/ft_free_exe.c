/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_exe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 21:25:00 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/15 15:03:05 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"
#include <stdlib.h>

void	ft_free_lsther(t_lsther *lst)
{
	if (!lst)
		return ;
	ft_free_lsther(lst->next);
	lst->next = NULL;
	free(lst->name);
	lst->name = NULL;
	free(lst);
}

void	ft_free_lstred(t_lstred *lst)
{
	if (!lst)
		return ;
	ft_strdel(&lst->name_og);
	ft_strdel(&lst->name_dir);
	ft_free_lstred(lst->next);
	lst->next = NULL;
	free(lst);
}

void	ft_free_tab(char **tabl)
{
	int	k;

	k = 0;
	if (!tabl)
		return ;
	while (tabl[k])
	{
		free(tabl[k]);
		k++;
	}
	free(tabl);
}

void	ft_free_red(t_red *red)
{
	if (!red)
		return ;
	ft_free_red(red->next);
	red->next = NULL;
	ft_free_lsther(red->lsther);
	red->lsther = NULL;
	if (red->end_nm)
		free(red->end_nm);
	red->end_nm = NULL;
	free(red);
}

void	ft_free_cmd(t_launch *cmd)
{
	if (!cmd)
		return ;
	ft_free_cmd(cmd->next);
	cmd->next = NULL;
	ft_free_red(cmd->red);
	cmd->red = NULL;
	ft_free_tab(cmd->argv);
	cmd->argv = NULL;
	if (cmd->fdpipe)
		free(cmd->fdpipe);
	cmd->fdpipe = NULL;
	free(cmd);
}
