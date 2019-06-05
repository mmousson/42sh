/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 14:45:41 by hben-yah          #+#    #+#             */
/*   Updated: 2019/06/04 21:30:41 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"
#include "libft.h"

t_globtok		*globlex_append(t_globlex *container, void *data)
{
	t_globtok	*new;
	t_globtok	*ptr;

	if (!data || !(new = globtoknew(data)))
		return (0);
	if (!(ptr = container->first))
		container->first = new;
	else
	{
		ptr = container->last;
		new->prev = ptr;
		ptr->next = new;
	}
	container->last = new;
	++container->len;
	return (new);
}

t_globtok		*globlex_prepend(t_globlex *container, void *data)
{
	t_globtok	*new;
	t_globtok	*ptr;

	if (!data || !(new = globtoknew(data)))
		return (0);
	if (!(ptr = container->last))
		container->last = new;
	else
	{
		ptr = container->first;
		new->next = ptr;
		ptr->prev = new;
	}
	container->first = new;
	++container->len;
	return (new);
}

static void			*get_token(char **pattern)
{
	if (**pattern == '*')
		return (glob_new_chr_token(GLO_STAR, pattern));
	if (**pattern == '?')
		return (glob_new_chr_token(GLO_QUEST, pattern));
	if (**pattern == '[')
		return (glob_new_range_token(GLO_RANGE, pattern));
	return (glob_new_str_token(GLO_CONST, pattern));
}

int					tokenize_word_pattern(t_submatch *gl)
{
	char		*pattern;
	t_str_token	*token;

	pattern = gl->word;
	while (*pattern)
	{
		if ((token = get_token(&pattern)))
		{
			if (token->type == GLO_CONST)
				token->len = expansion_unquote(token->value);
			if (gl->suffix)
			{
				if (token->type == GLO_CONST)
					ft_strrev(token->value);
				globlex_prepend(gl->lexer, token);
			}
			else
				globlex_append(gl->lexer, token);
		}
	}
	return (!gl->lexer || !gl->lexer->first);
}
