/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:52:38 by hben-yah          #+#    #+#             */
/*   Updated: 2019/05/28 17:45:31 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arithmetic.h"
#include "libft.h"

t_arithtok
	*token_new(char *val, size_t length, int type, t_arithtok *next)
{
	t_arithtok *new;

	if (!(new = (t_arithtok*)ft_memalloc(sizeof(t_arithtok))))
		return (NULL);
	if (!(new->val = ft_strsub(val, 0, length)))
		return (NULL);
	new->length = length;
	new->type = type;
	new->next = next;
	return (new);
}

t_arithtok
	*token_dup(t_arithtok *tok)
{
	t_arithtok *new;

	if (!(new = ft_memalloc(sizeof(t_arithtok))))
		return (NULL);
	if (tok->val && !(new->val = ft_strdup(tok->val)))
		return (NULL);
	new->length = tok->length;
	new->type = tok->type;
	new->valid = tok->valid;
	new->next = NULL;
	return (new);
}

void
	tokenlist_del(t_arithtok **token)
{
	t_arithtok *tok;
	t_arithtok *tmp;

	if (token && *token)
	{
		tok = *token;
		while (tok)
		{
			tmp = tok;
			ft_strdel(&tmp->val);
			tok = tmp->next;
			free(tmp);
		}
		*token = NULL;
	}
}

void
	token_del(t_arithtok **tok)
{
	t_arithtok *todel;

	if (tok && *tok)
	{
		todel = *tok;
		*tok = (*tok)->next;
		ft_strdel(&todel->val);
		todel->next = NULL;
		free(todel);
	}
}
