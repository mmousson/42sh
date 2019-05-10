/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 17:11:31 by oboutrol          #+#    #+#             */
/*   Updated: 2019/04/06 21:18:21 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include <stdlib.h>
#include "libft.h"

void		ft_add_token(char buf[BUF], char *load, int stat, t_tok *tok)
{
	t_tok	*tmp;
	t_tok	*new;

	tmp = tok;
	while (tmp->next)
		tmp = tmp->next;
	if (!(new = ft_init_token()))
		return ;
	tmp->next = new;
	if (load)
		new->content = ft_strjoin(load, buf);
	else
		new->content = ft_strdup(buf);
	new->next = NULL;
	new->status = stat;
	buf[0] = '\0';
}

void		ft_add_char(char buf[BUF], char **load, char cha)
{
	int		size;

	size = ft_strlen(buf);
	if (size >= BUF - 1)
	{
		if (!(*load))
			*load = ft_strdup(buf);
		else
			*load = ft_strjoin(*load, buf);
		buf[0] = cha;
	}
	else
	{
		buf[size] = cha;
		buf[size + 1] = 0;
	}
}
