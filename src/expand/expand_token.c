/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 10:19:28 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/03 23:43:49 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"
#include "expand.h"
#include <stdlib.h>

#include "libft.h"
int		expand_token(t_tok *token, char ***arge)
{
	int	ret;

	if (!token || pars_is_delimiter(token->status))
		return (0);
	if (is_charkind(token->status))
	{
		if ((ret = expand_manager(&token->content, arge, token)))
		{
			if (ret == -1)
			{
				lex_free_token(token->next);
				token->next = NULL;
				return (1);
			}
			return (1);
		}
	}
	if (expand_token(token->next, arge))
		return (1);
	return (0);
}
