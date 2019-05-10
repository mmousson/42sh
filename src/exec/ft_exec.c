/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 08:07:28 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/04 16:32:00 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"
#include "libft.h"
#include <stdlib.h>

void			ft_add_argv(char *str, t_launch *cmd)
{
	char		**tabl;

	if (!(tabl = extend(cmd->argv, str)))
		return ;
	if (cmd->argv)
		free(cmd->argv);
	cmd->argv = tabl;
}

static t_launch	*ft_last(t_launch *cmd)
{
	t_launch	*last;

	last = cmd;
	while (last->next)
		last = last->next;
	return (last);
}

static void		ft_add_elmt(t_tree *tree, t_launch **cmd, t_red **red)
{
	if (ft_last(*cmd)->will_red == 1)
	{
		*red = ft_target_last(ft_last(*cmd));
		(*red)->end_nm = ft_strdup(tree->content);
		ft_last(*cmd)->will_red = 0;
	}
	else
		ft_add_argv(ft_strdup(tree->content), ft_last(*cmd));
}

static void		ft_add(t_tree *tree, t_launch **cmd, char ***arge)
{
	t_red		*red;
	int			ret;

	if (!tree)
		return ;
	if ((ret = ft_add_red(tree, ft_last(*cmd))))
	{
		ft_add(tree->left, cmd, arge);
		if (tree->content)
			ft_add_elmt(tree, cmd, &red);
		if (tree->type == PIP)
		{
			(*cmd)->nbr_pipe++;
			ft_next_pipe(ft_last(*cmd));
		}
		if (tree->type == SMC)
		{
			ft_launch_cmd(cmd, arge);
			tree->right = ft_expend(tree->right, *arge);
		}
	}
	if (ret || ft_last(*cmd)->will_red == -1)
		ft_add(tree->right, cmd, arge);
}

void			ft_exec(t_tree *tree, char ***arge)
{
	t_launch	*cmd;

	if (!(cmd = ft_init_cmd(NULL)))
		return ;
	tree = ft_expend(tree, *arge);
	ft_add(tree, &cmd, arge);
	ft_free_tree(tree);
	ft_launch_cmd(&cmd, arge);
	ft_free_cmd(cmd);
}
