/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 19:16:45 by oboutrol          #+#    #+#             */
/*   Updated: 2019/04/25 13:00:05 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

int			ft_pars(t_tok *token, char ***arge, t_env *env)
{
	t_tree	*tree;

	(void)env;
	(void)arge;
	//ft_print_token(token);
	tree = ft_pars_line(token->next, 0, -2);
	//ft_print_tree(tree);
	//ft_exec(tree, arge, env);
	return (0);
}
