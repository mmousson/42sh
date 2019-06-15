/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_alias.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 08:10:04 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/15 15:42:21 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "pars.h"
#include "expand.h"
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

	if (!str)
		return (0);
	k = -1;
	while (++k < NBR_RES)
	{
		if (!ft_strcmp(str, list[k]))
			return (1);
	}
	return (0);
}

static int		is_space(char *str)
{
	int			k;

	if (!str)
		return (0);
	k = -1;
	while (str[++k])
		if (str[k] == ' ' && !str[k + 1])
			return (1);
	return (0);
}

int				replace_tok(char **str, char *value, char *exp, t_stat *stat)
{
	int			k;

	k = value ? ft_strlen(value) : 0;
	insert_word(str, exp, stat->k - k + 1, k - 1);
	stat->k = stat->k - k + 1 + ft_strlen(exp);
	while (exp && exp[0] && is_space(exp))
	{
		ft_strdel(&value);
		value = grep_next_word(*str + stat->k, stat);
		ft_strdel(&exp);
		if ((exp = get_alias(value)))
		{
			k = value ? ft_strlen(value) : 0;
			insert_word(str, exp, stat->k - k + 1, k - 1);
			stat->k = stat->k - k + 1 + ft_strlen(exp);
		}
	}
	ft_strdel(&value);
	ft_strdel(&exp);
	stat->unalias = stat->k;
	stat->k = -1;
	stat->status = 0;
	return (1);
}

int				expand_alias(char **str, char *word, t_stat *stat)
{
	char		*exp;

	if (stat->k < stat->unalias || is_reserved(word))
		return (0);
	if ((exp = get_alias(word)))
	{
		return (replace_tok(str, word, exp, stat));
	}
	return (0);
}
