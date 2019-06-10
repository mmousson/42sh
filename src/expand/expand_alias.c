/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_alias.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 08:10:04 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/10 13:17:31 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "pars.h"
#include "lex.h"
#include "libft.h"
#define NBR_RES 13

int				is_reserved(char *str)
{
	int			k;
	static char	*list[NBR_RES] = {
		"case", "do", "done", "elif", "else",
		"esac", "fi", "for", "if", "in",
		"then", "until", "while"
	};

	k = -1;
	while (++k < NBR_RES)
	{
		if (!ft_strcmp(str, list[k]))
			return (1);
	}
	return (0);
}

void			replace_tok(t_tok *token, char *str)
{
	char		**tab;
	t_tok		*end;
	t_tok		*tmp;
	int			k;

	if (!str)
		return ;
	tab = ft_strsplit(str, ' ');
	tmp = token;
	end = token->next;
	if (tab && tab[0])
	{
		ft_strdel(&token->content);
		token->content = tab[0];
		k = 0;
		while (tab[++k])
		{
			tmp->next = new_token_space();
			tmp = tmp->next;
			tmp->next = new_token_char(tab[k]);
			tmp = tmp->next;
		}
		free(tab);
		tmp->next = end;
	}
}

void			expand_alias(t_tok *token)
{
	t_alias		*tmp;

	if (!token || !token->content)
		return ;
	if (is_reserved(token->content))
		return ;
	tmp = g_alias_list;
	while (tmp)
	{
		if (!ft_strcmp(tmp->token, token->content))
			return (replace_tok(token, tmp->replacement));
		tmp = tmp->next;
	}
}
