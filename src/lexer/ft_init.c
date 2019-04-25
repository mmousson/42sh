/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 13:41:35 by oboutrol          #+#    #+#             */
/*   Updated: 2019/04/06 18:31:26 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include <stdlib.h>

t_tok			*ft_init_token(void)
{
	t_tok		*token;

	if (!(token = (t_tok*)malloc(sizeof(t_tok))))
		return (NULL);
	token->next = NULL;
	token->content = NULL;
	token->status = 0;
	return (token);
}

t_stat			*ft_init_stat(void)
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
