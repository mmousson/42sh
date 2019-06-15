/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_grep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 15:09:16 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/15 16:36:29 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

char		*grep_next_word(char *str, t_stat *stat)
{
	int		start;
	char	*word;
	int		k;

	k = 0;
	word = NULL;
	while (str[k] == ' ')
		k++;
	start = k;
	while (str[k] && str[k] != ' ')
		k++;
	if (k > start)
		word = ft_strsub(str, start, k - start);
	stat->k += k - 1;
	return (word);
}

static int	is_sep_cmd(char *word, int k)
{
	if (word[k] == ';')
		return (1);
	if (word[k] == '&' && (word[k + 1] == '&' || (k > 0 && word[k - 1] == '&')))
		return (1);
	if (word[k] == '|' && (word[k + 1] == '|' || (k > 0 && word[k - 1] == '|')))
		return (1);
	return (0);
}

char		*grep_iter(char *word, int iter, int *start)
{
	int		k;
	int		j;
	int		end;
	char	*sub;

	k = 0;
	j = 0;
	*start = 0;
	while (word && word[k] && j <= iter && (*start = k) >= 0)
	{
		while (word[k] && word[k] != ' ')
			k++;
		end = k;
		while (word[k] && !is_sep_cmd(word, k))
			k++;
		while (is_sep_cmd(word, k))
			k++;
		while (word[k] && word[k] == ' ')
			k++;
		j++;
	}
	if (iter >= j)
		return (NULL);
	sub = ft_strsub(word, *start, end);
	return (sub);
}
