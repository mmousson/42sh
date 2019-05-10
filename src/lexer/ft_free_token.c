/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 20:22:00 by oboutrol          #+#    #+#             */
/*   Updated: 2019/04/30 20:33:18 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include <stdlib.h>

void	ft_free_token(t_tok *token)
{
	if (!token)
		return ;
	ft_free_token(token->next);
	if (token->content)
	{
		free(token->content);
		token->content = NULL;
	}
	free(token);
}
