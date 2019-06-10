/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 08:32:17 by hben-yah          #+#    #+#             */
/*   Updated: 2019/06/10 16:31:33 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"
#include "libft.h"

t_chr_token			*glob_new_chr_token(int type, char **str)
{
	t_chr_token	*new;

	if (!str || !*str || !(new = (t_chr_token *)ft_memalloc(sizeof(*new))))
		return (NULL);
	new->type = type;
	new->value = **str;
	if (type != GLO_HIDE || **str == '.')
		++(*str);
	return (new);
}

t_str_token			*glob_new_str_token(int type, char **str)
{
	t_str_token	*new;
	char		*start;

	if (!str || !*str || !(new = (t_str_token*)ft_memalloc(sizeof(*new))))
		return (NULL);
	start = (*str)++;
	walk_const(str);
	new->len = *str - start;
	if (!(new->value = ft_strsub(start, 0, new->len)))
	{
		free(new);
		return (NULL);
	}
	new->len = expansion_unquote(new->value);
	new->type = type;
	return (new);
}

t_rng_token			*glob_new_range_token(int type, char **rng)
{
	t_rng_token	*new;
	char		*beg;

	if (!rng || !*rng || !(new = (t_rng_token *)ft_memalloc(sizeof(*new))))
		return (NULL);
	beg = *rng;
	if (walk_range(rng))
	{
		free(new);
		return (NULL);
	}
	if (!(new->value = ft_strsub(beg, 0, *rng - beg + 1)))
	{
		free(new);
		return (NULL);
	}
	new->type = type;
	if (*(new->value + 1) == '!')
		new->negative = 1;
	parse_range(new->allow, new->value + 1 + new->negative);
	if (**rng == ']')
		++*rng;
	return (new);
}

static void			*get_token(char **path, void *prev)
{
	t_rng_token *rng;
	char		*ptr;

	if (!prev || ((t_chr_token *)prev)->type == GLO_SEPAR)
		return (glob_new_chr_token(GLO_HIDE, path));
	if (**path == '*')
		return (glob_new_chr_token(GLO_STAR, path));
	if (**path == '?')
		return (glob_new_chr_token(GLO_QUEST, path));
	if (**path == '/')
		return (glob_new_chr_token(GLO_SEPAR, path));
	if (**path == '[')
	{
		ptr = *path;
		if ((rng = glob_new_range_token(GLO_RANGE, path)) || ptr != *path)
			return (rng);
	}
	return (glob_new_str_token(GLO_CONST, path));
}

int					tokenize(t_glob *gl)
{
	char		*path;
	t_str_token	*token;
	t_str_token	*prev;

	path = gl->expr;
	prev = NULL;
	while (*path)
		if ((token = get_token(&path, prev)))
		{
			globlex_pushback(gl->lexer, token);
			prev = token;
		}
	return (!gl->lexer || !gl->lexer->first);
}
