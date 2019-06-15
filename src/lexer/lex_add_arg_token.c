/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_add_arg_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 15:08:36 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/14 15:17:54 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

void		lex_add_arg_token(t_tok *token, char *content, int status)
{
	t_tok	*tmp;
	t_tok	*new;

	tmp = token;
	if (!(new = lex_init_token()))
		return ;
	new->content = content;
	new->status = status;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp)
		tmp->next = new;
}
