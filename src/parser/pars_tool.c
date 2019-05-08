/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_tool.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 18:36:17 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/08 21:41:52 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"
#include "libft.h"
#include <stdlib.h>

int			is_sepa_tok(t_tok *token)
{
	if (token)
	{
		if (token->status == ESP)
		{
			if (!ft_strcmp(token->content, "&&"))
				token->status += DBL;
			return (1);
		}
		else if (token->status == SMC)
			return (1);
		else if (token->status == PIP && !ft_strcmp(token->content, "||"))
		{
			token->status += DBL;
			return (1);
		}
	}
	return (0);
}

int			is_sep(int status)
{
	if (status == SMC || status == ESP + DBL || status == PIP + DBL
			|| status == ESP)
		return (1);
	return (0);
}

int			tok_is_stat(t_tok *token, int status)
{
	if (token->status == status)
		return (1);
	if (status == SMC && is_sep(token->status))
		return (1);
	return (0);
}

t_tok		*ft_go_status(t_tok *token, int *pos, int status, int end)
{
	t_tok	*tmp;

	tmp = token;
	while (tmp && !tok_is_stat(tmp, status) && (end == -2 || *pos < end))
	{
		tmp = tmp->next;
		(*pos)++;
	}
	return (tmp);
}

t_tok		*ft_go_start(t_tok *token, int start)
{
	t_tok	*tok;

	tok = token;
	if (tok == NULL)
		return (NULL);
	while (tok && start)
	{
		tok = tok->next;
		start--;
	}
	if (start != 0)
		return (NULL);
	return (tok);
}
