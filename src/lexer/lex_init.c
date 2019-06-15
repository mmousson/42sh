/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:03:18 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/13 07:50:10 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include <stdlib.h>

t_st			*init_pile(int status)
{
	t_st		*new;

	if (!(new = (t_st*)malloc(sizeof(t_st))))
		return (NULL);
	new->elmt = status;
	new->next = NULL;
	return (new);
}

t_tok			*lex_init_token(void)
{
	t_tok		*token;

	if (!(token = (t_tok*)malloc(sizeof(t_tok))))
		return (NULL);
	token->next = NULL;
	token->content = NULL;
	token->status = 0;
	return (token);
}

t_stat			*lex_init_stat(void)
{
	t_stat		*stat;

	if (!(stat = (t_stat*)ft_memalloc(sizeof(t_stat))))
		return (NULL);
	stat->unalias = -1;
	return (stat);
}

t_tok			*new_token_char(char *str)
{
	t_tok		*new;

	if (!(new = lex_init_token()))
		return (NULL);
	new->content = str;
	new->status = CHA;
	return (new);
}

t_tok			*new_token_space(void)
{
	t_tok		*new;

	if (!(new = lex_init_token()))
		return (NULL);
	new->content = ft_strdup(" ");
	new->status = SPA;
	return (new);
}
