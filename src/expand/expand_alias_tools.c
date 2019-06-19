/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_alias_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 20:43:45 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/18 14:29:16 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "pars.h"
#include "expand.h"
#include "lex.h"
#include "libft.h"

static void	add_file(t_tok *names, char *content)
{
	t_tok	*tmp;
	t_tok	*new;

	tmp = names;
	if (!(new = lex_init_token()))
		return ;
	new->content = ft_strdup(content);
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp)
		tmp->next = new;
}

static char	*get_multi_alias(char *word, t_tok *names)
{
	t_tok	*tmp;
	t_alias	*alias;

	tmp = names;
	if (is_reserved(word))
		return (NULL);
	while (tmp)
	{
		if (tmp->content && !ft_strcmp(word, tmp->content))
			return (NULL);
		tmp = tmp->next;
	}
	alias = g_alias_list;
	while (alias)
	{
		if (!ft_strcmp(alias->token, word))
		{
			add_file(names, word);
			return (ft_strdup(alias->replacement));
		}
		alias = alias->next;
	}
	return (NULL);
}

static int	loop_iter(char **exp, t_tok *names)
{
	int		k;
	int		loop;
	int		start;
	char	*sub;
	char	*sub_exp;

	loop = 0;
	k = 0;
	start = 0;
	while ((sub = grep_iter(*exp, k, &start)))
	{
		if ((sub_exp = get_multi_alias(sub, names)))
		{
			insert_word(exp, sub_exp, start, start + ft_strlen(sub) - 1);
			loop = 1;
			ft_strdel(&sub_exp);
		}
		ft_strdel(&sub);
		k++;
	}
	return (loop);
}

char		*get_alias(char *word)
{
	t_tok	*names;
	char	*exp;
	int		loop;
	int		it;

	names = lex_init_token();
	it = 0;
	if ((loop = 1) && is_reserved(word))
		return (NULL);
	exp = get_multi_alias(word, names);
	while (it < 80 && exp && loop && !((loop = 0)))
	{
		loop = loop_iter(&exp, names);
		it++;
	}
	lex_free_token(names);
	return (exp);
}
