/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_part.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 19:43:04 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/28 16:05:59 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"
#include "libft.h"
#define NB_CHAR_KIND 4

int			is_charkind(int st)
{
	int			pos;
	static int	lst_stat[NB_CHAR_KIND] = {
		CHA, DOL, DQT, SQT};

	pos = 0;
	while (pos < NB_CHAR_KIND)
	{
		if (st == lst_stat[pos])
			return (1);
		pos++;
	}
	return (0);
}

t_tree		*ft_pars_part(t_tok *token, int start, int end)
{
	t_tok	*tok;
	t_tree	*tree;

	tok = ft_go_start(token, start);
	if (tok == NULL || (end != -2 && start != end))
		return (NULL);
	if (tok == NULL || (end == -2 && tok->next != NULL))
		return (NULL);
	if (is_charkind(tok->status))
	{
		if (!(tree = ft_end_branch()))
			return (NULL);
		tree->type = tok->status;
		if (tok->content)
			tree->content = ft_strdup(tok->content);
		return (tree);
	}
	return (NULL);
}
