/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expend.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:04:52 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/06 22:04:42 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"
#include "pars.h"
#include <stdlib.h>
#include "libft.h"

static char		*ft_cmpct_exp(t_tree *tree, char **arge)
{
	char		*ret;
	char		*beg;
	char		*end;

	ret = NULL;
	beg = ft_cmpct(tree->left, arge);
	end = ft_cmpct(tree->right, arge);
	if (beg && end)
		ret = ft_strjoin(beg, end);
	else if (beg)
		ret = ft_strdup(beg);
	else if (end)
		ret = ft_strdup(end);
	ft_strdel(&beg);
	ft_strdel(&end);
	return (ret);
}

char			*ft_cmpct(t_tree *tree, char **arge)
{
	char		*ret;

	ret = NULL;
	if (!tree)
		return (NULL);
	if (tree->type == EXP)
		ret = ft_cmpct_exp(tree, arge);
	else if (is_clean(tree->type))
		return (ft_strdup(tree->content));
	else if (tree->type == DOL)
		ret = ft_doll(tree, arge);
	else if (tree->type == TIL)
		return (ft_strdup("~"));
	return (ret);
}

static t_tree	*ft_reduce(t_tree *tree, char **arge)
{
	t_tree		*compact;

	if ((compact = ft_end_branch()))
	{
		compact->type = CHA;
		compact->content = ft_cmpct(tree, arge);
	}
	ft_free_tree(tree);
	tree = NULL;
	return (compact);
}

static t_tree	*ft_cmpct_til(t_tree *tree, char **arge)
{
	char		*str;
	char		*tmp;

	tree->type = CHA;
	tree->content = ft_getenv(arge, "HOME");
	if (tree->right)
	{
		str = ft_cmpct(tree->right, arge);
		if (str)
		{
			tmp = tree->content;
			tree->content = ft_strjoin(tmp, str);
			ft_strdel(&str);
			ft_strdel(&tmp);
		}
		ft_free_tree(tree->right);
		tree->right = NULL;
	}
	return (tree);
}

t_tree			*ft_expend(t_tree *tree, char **arge)
{
	char		*tmp;

	if (!tree || !arge)
		return (NULL);
	if (tree->type == TIL)
		tree = ft_cmpct_til(tree, arge);
	else if (tree->type == EXP)
		tree = ft_reduce(tree, arge);
	else if (tree->type == DOL)
	{
		tree->type = CHA;
		tmp = tree->content;
		tree->content = ft_doll(tree, arge);
		if (tmp)
			free(tmp);
	}
	else
	{
		tree->left = ft_expend(tree->left, arge);
		if (tree->type != SMC)
			tree->right = ft_expend(tree->right, arge);
	}
	return (tree);
}
