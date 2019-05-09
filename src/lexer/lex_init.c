/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:03:18 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/09 15:13:55 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include <stdlib.h>

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

	if (!(stat = (t_stat*)malloc(sizeof(t_stat))))
		return (NULL);
	stat->status = 0;
	stat->old_status = 0;
	stat->ch = 0;
	stat->cha = '\0';
	stat->k = 0;
	stat->load = NULL;
	return (stat);
}
