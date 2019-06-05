/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_substring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 14:40:16 by hben-yah          #+#    #+#             */
/*   Updated: 2019/06/05 11:36:43 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"
#include "libft.h"

void	walk_const(char **s)
{
	while (**s)
	{
		if (**s == '[' || **s == '*' || **s == '?')
			break ;
		if (**s == '\\')
			++*s;
		else if (is_quote(**s))
			walk_quote(s);
		**s && ++*s;
	}
}

static void	free_submatch(t_submatch *sm)
{
	free(sm->param);
	free(sm->word);
	globlexdel(&sm->lexer);
}

static char	*get_match(t_submatch *sm)
{
	char *ptr;

	if ((ptr = match_word(sm->lexer->first, sm->param, sm->greedy)))
		return (ft_strdup(ptr));
	else
		return (ft_strdup(sm->param));
	return (NULL);
}

char	*remove_substring(char *param, char *word, int suffix, int greedy)
{
	t_submatch sm;
	char *res;

	ft_bzero(&sm, sizeof(sm));
	sm.suffix = suffix;
	sm.greedy = greedy;
	sm.param = param;
	if (!(sm.param = ft_strdup(param))
		|| !(sm.word = ft_strdup(word)))
		return (NULL);
	if (suffix)
		ft_strrev(sm.param);
	if (!(sm.lexer = globlexnew(0))
		|| tokenize_word_pattern(&sm))	
	{
		free_submatch(&sm);
		return (NULL);
	}
	res = get_match(&sm);
	free_submatch(&sm);
	if (res && suffix)
		ft_strrev(res);
	return (res);
}
