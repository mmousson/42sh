/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 13:45:34 by oboutrol          #+#    #+#             */
/*   Updated: 2019/04/13 07:37:18 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"
#include "libft.h"

void		ft_print_sp(int sp)
{
	while (sp > 0)
	{
		ft_putchar(' ');
		sp--;
	}
}

void		ft_print_one(int sp, t_tree *tree)
{
	if (!tree)
		return ;
	ft_print_ch_hash(tree->type);
	if (tree->content)
	{
		ft_putstr(" ");
		ft_putstr(tree->content);
	}
	ft_putchar(' ');
	ft_print_one(sp + 4, tree->right);
	if (tree->left)
	{
		ft_putchar('\n');
		ft_print_sp(sp + 4);
		ft_print_one(sp + 4, tree->left);
	}
}

void		ft_print_tree(t_tree *tree)
{
	ft_putchar('\n');
	if (!tree)
		ft_putstr_fd("No working tree found", 2);
	else
		ft_print_one(0, tree);
	ft_putchar('\n');
}
