/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 08:32:17 by hben-yah          #+#    #+#             */
/*   Updated: 2019/05/27 19:31:28 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"
#include "libft.h"

static t_chr_token	*glob_new_chr_token(int type, char **str)
{
	t_chr_token	*new;

	if (!str || !*str || !(new = (t_chr_token *)ft_memalloc(sizeof(*new))))
		return (NULL);
	new->type = type;
	new->value = **str;
	++(*str);
	return (new);
}

static t_str_token	*glob_new_str_token(int type, char **str)
{
	t_str_token	*new;
	char		*start;

	if (!str || !*str || !(new = (t_str_token*)ft_memalloc(sizeof(*new))))
		return (NULL);
	start = *str;
	walk_word(str);
	new->len = *str - start;
	if (!(new->value = ft_strsub(start, 0, new->len)))
	{
		free(new);
		return (NULL);
	}
	expansion_unquote(new->value);
	new->type = type;
	return (new);
}

static t_rng_token	*glob_new_range_token(int type, char **rng)
{
	t_rng_token	*new;
	char		*beg;

	if (!rng || !*rng || !(new = (t_rng_token *)ft_memalloc(sizeof(*new))))
		return (NULL);
	beg = *rng;
	walk_range(rng);
	if (!(new->value = ft_strsub(beg, 0, *rng - beg + 1)))
	{
		free(new);
		return (NULL);
	}
	new->type = type;
	if (*(new->value + 1) == '!')
		new->negative = 1;
	parse_range(new->allow, new->value + 1 + new->negative);
	**rng == ']' && ++*rng;
	return (new);
}

static void			*get_token(char **path)
{
	if (**path == '*')
		return (glob_new_chr_token(GLO_STAR, path));
	if (**path == '?')
		return (glob_new_chr_token(GLO_QUEST, path));
	if (**path == '[')
		return (glob_new_range_token(GLO_RANGE, path));
	if (**path == '/')
		return (glob_new_chr_token(GLO_SEPAR, path));
	return (glob_new_str_token(GLO_CONST, path));
}

int					tokenize(t_glob *gl)
{
	char		*path;
	t_str_token	*token;

	path = gl->expr;
	while (*path)
	{
		if ((token = get_token(&path)))
		{
			if (token->type == GLO_CONST)
				expansion_unquote(token->value);
			globlex_pushback(gl->lexer, token);
		}
	}
	return (!gl->lexer || !gl->lexer->first);
}
