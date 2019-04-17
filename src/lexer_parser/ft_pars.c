/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 03:15:19 by oboutrol          #+#    #+#             */
/*   Updated: 2019/04/07 18:08:52 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexpars.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include "built_in.h"

int				ft_launch_fct(t_args *args, int fct, char **path, char ***arge)
{
	char		**tabl;

	if (fct == 0)
	{
		if (path && *path)
			free(*path);
		ft_exit_clean_args(args, 0);
	}
	if (!(tabl = ft_make_tabl(args->cmd->word)))
		return (1);
	if (fct == -2)
	{
		if (!(do_fork(*path, tabl, *arge, args)))
			return (1);
		ft_strdel(path);
	}
	else
	{
		if (ft_launch_red(args->cmd->redir, args))
			ft_exit_clean_args(args, 1);
		ft_do_home(fct, tabl, arge);
		ft_res_red(args);
	}
	ft_del_words_tables(&tabl);
	return (0);
}

int				ft_exec(t_cmd *cmd, char ***arge, t_args *args)
{
	int			fct;
	char		*path;

	path = NULL;
	if ((fct = ft_fct(cmd->word, &path, *arge)) != -1)
	{
		args->cmd = cmd;
		if (ft_launch_fct(args, fct, &path, arge))
			return (1);
	}
	else
	{
		if (ft_launch_red(cmd->redir, args))
			ft_exit_clean_args(args, 1);
		if (cmd->word && cmd->word->value)
		{
			ft_putstr_fd("21sh: command not found: ", 2);
			ft_putstr_fd(cmd->word->value, 2);
			ft_putchar_fd('\n', 2);
		}
		ft_res_red(args);
	}
	return (0);
}

int				ft_pars(t_cmd *cmd, char ***arge, t_args *args, int ret)
{
	t_cmd		*tmp;
	int			skip;

	tmp = cmd;
	skip = 0;
	if (ret == -2)
		return (0);
	while (cmd)
	{
		if (!(skip = ft_manage_pipe(cmd, arge, args)))
		{
			if (ft_exec(cmd, arge, args))
				return (1);
			cmd = cmd->next;
		}
		else
			while (skip + 1 && cmd)
			{
				skip--;
				cmd = cmd->next;
			}
	}
	cmd = tmp;
	args->cmd = cmd;
	return (0);
}
