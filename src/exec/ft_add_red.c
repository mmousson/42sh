/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_red.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 17:23:19 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/04 16:24:56 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"
#include "libft.h"

static int		is_red(t_tree *tree)
{
	if (!tree)
		return (0);
	if (tree->type == RER || tree->type == REL || tree->type == RER + 20
			|| tree->type == REL + 20)
		return (1);
	return (0);
}

static void		ft_set_red(t_red **red, t_tree *tree, t_launch *cmd)
{
	t_tree		*tmp;

	tmp = tree;
	if (is_red(tmp))
	{
		tmp = tmp->left;
		cmd->will_red = -1;
	}
	else
		cmd->will_red = 0;
	if (tmp)
	{
		if (tmp->type == INT)
			if (tmp->content && tmp->content[0] == '&')
				(*red)->end = ft_atoi(tmp->content + 1);
		if (tmp->type == DAS)
			(*red)->end = -2;
		(*red)->end_nm = ft_strdup(tmp->content);
	}
}

static t_red	*ft_target_red(t_launch *cmd)
{
	t_red		*red;

	red = cmd->red;
	while (red->type && red->next)
		red = red->next;
	if (red->type)
	{
		red->next = ft_init_red();
		red = red->next;
	}
	return (red);
}

t_red			*ft_target_last(t_launch *cmd)
{
	t_red		*red;

	red = cmd->red;
	while (red->next && red->next->type)
		red = red->next;
	return (red);
}

int				ft_add_red(t_tree *tree, t_launch *cmd)
{
	t_red		*red;

	if (tree->type == RER || tree->type == REL)
	{
		red = ft_target_red(cmd);
		red->type = tree->type;
		if (tree->content && (!ft_strcmp(tree->content, ">>")
					|| !ft_strcmp(tree->content, "<<")))
			red->type += 20;
		if (tree->left && cmd->will_red != -1)
		{
			if (tree->left->type == INT)
				red->srt = ft_atoi(tree->left->content);
			else if (tree->left->content)
				ft_add_argv(ft_strdup(tree->left->content), cmd);
		}
		if (tree->right)
			ft_set_red(&red, tree->right, cmd);
		else
			cmd->will_red = 1;
		return (0);
	}
	return (1);
}
