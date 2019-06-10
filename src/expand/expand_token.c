/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 10:19:28 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/10 14:59:01 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"
#include "expand.h"
#include <stdlib.h>
#include "libft.h"

int		ret_if_neg(t_tok *token, int ret)
{
	if (ret == -1)
	{
		lex_free_token(token->next);
		token->next = NULL;
		return (1);
	}
	return (1);
}

int		expand_token(t_tok *token, char ***arge, int here, int red)
{
	int	ret;

	if (!token || pars_is_delimiter(token->status))
		return (0);
	if (is_charkind(token->status))
	{
		if (here)
			here = 0;
		else if ((ret = expand_manager(&token->content, arge, token, red)))
			return (ret_if_neg(token, ret));
		if (red)
			red = 0;
	}
	if (token->status == REL && !ft_strcmp(token->content, "<<"))
		here = 1;
	else if (token->status == RER || token->status == REL)
		red = 1;
	if (expand_token(token->next, arge, here, red))
		return (1);
	return (0);
}
