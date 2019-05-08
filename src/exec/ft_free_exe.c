/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_exe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 21:25:00 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/06 15:43:26 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"
#include <stdlib.h>

void	ft_free_lstfd(t_lstfd *lst)
{
	if (!lst)
		return ;
	ft_free_lstfd(lst->next);
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
	ft_free_lstfd(cmd->lstfd);
	cmd->lstfd = NULL;
	if (cmd->fdpipe)
		free(cmd->fdpipe);
	cmd->fdpipe = NULL;
	free(cmd);
}
