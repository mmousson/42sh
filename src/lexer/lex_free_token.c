/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_free_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:49:38 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/28 18:22:00 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

void	lex_free_token(t_tok *token)
{
	if (!token)
		return ;
	lex_free_token(token->next);
	if (token->content)
	{
		free(token->content);
		token->content = NULL;
	}
	free(token);
}
