/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_pattern.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 14:44:16 by hben-yah          #+#    #+#             */
/*   Updated: 2019/06/05 11:57:21 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"
#include "libft.h"

static char
	*match_asterisk(t_globtok *tok, char *param, int greedy)
{
	char	*tmp;
	char	*ptr;
	int		match;

	match = 0;
	ptr = NULL;
	while (1)
	{
		tmp = match_word(tok->next, param, greedy);
		if (tmp)
			match = 1;
		if (tmp && (!ptr || (greedy && tmp > ptr) || (!greedy && tmp < ptr)))
			ptr = tmp;
		if (!*(param++))
			break ;
	}
	return (match ? ptr : NULL);
}

static char
	*match_question(t_globtok *tok, char *param, int greedy)
{
	char *ptr;

	ptr = NULL;
	if (*param)
		ptr = match_word(tok->next, param + 1, greedy);
	return (ptr);
}

static char
	*match_const(t_globtok *tok, t_str_token *tkn, char *param, int greedy)
{
	if (ft_strnequ(tkn->value, param, tkn->len))
		return (match_word(tok->next, param + tkn->len, greedy));
	return (NULL);
}

static char
	*match_range(t_globtok *tok, t_rng_token *tkn, char *param, int greedy)
{
	if ((!tkn->negative && tkn->allow[(unsigned char)*param])
		|| (tkn->negative && !tkn->allow[(unsigned char)*param]))
		return (match_word(tok->next, param + 1, greedy));
	return (NULL);
}

char
	*match_word(t_globtok *tok, char *param, int greedy)
{
	t_chr_token	*data;

	if (!tok)
		return (param);
	if (tok && tok->data)
	{
		data = (t_chr_token *)tok->data;
		if (data->type == GLO_STAR)
			return (match_asterisk(tok, param, greedy));
		if (data->type == GLO_QUEST)
			return (match_question(tok, param, greedy));
		if (data->type == GLO_CONST)
			return (match_const(tok, tok->data, param, greedy));
		if (data->type == GLO_RANGE)
			return (match_range(tok, tok->data, param, greedy));
	}
	return (NULL);
}
