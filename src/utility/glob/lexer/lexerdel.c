/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexerdel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 08:32:26 by hben-yah          #+#    #+#             */
/*   Updated: 2019/05/27 19:31:27 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"

void	globlexelemdel(t_globtok *tok)
{
	t_chr_token	*tkn;

	if (tok)
	{
		tkn = (t_chr_token*)tok->data;
		if (tkn)
		{
			if (tkn->type == GLO_CONST || tkn->type == GLO_RANGE)
				free(((t_str_token *)tkn)->value);
			free(tkn);
			tkn = 0;
		}
	}
}

void	globlexdel(t_globlex **container)
{
	t_globtok	*ptr;
	t_globtok	*tmp;

	if (container && *container)
	{
		ptr = (*container)->first;
		if (ptr)
		{
			while (ptr)
			{
				tmp = ptr->next;
				globlexelemdel(ptr);
				free(ptr);
				ptr = tmp;
			}
		}
		free(*container);
		*container = 0;
	}
}
