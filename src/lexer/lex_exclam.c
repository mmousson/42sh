/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_exclam.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 17:54:10 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/20 11:09:45 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include "history.h"

static void	process_sign(char **str, int *pos, char **sub, char buff[BUF])
{
	if ((*str)[*pos] == '-' && (*str)[*pos + 1])
	{
		lex_add_char(buff, sub, (*str)[*pos]);
		(*pos)++;
	}
	else if ((*str)[*pos] == '+' && (*str)[(*pos) + 1])
		(*pos)++;
}

static char	*lex_following(char **str, int pos, int *len)
{
	int		was_char;
	char	*sub;
	char	buff[BUF];

	sub = NULL;
	ft_bzero(buff, BUF);
	pos++;
	*len = pos;
	process_sign(str, &pos, &sub, buff);
	was_char = ft_isalpha((*str)[pos]);
	if ((*str)[pos] == '!' && (pos)++)
	{
		*len = 1;
		return (ft_strdup("!"));
	}
	while (ft_isdigit((*str)[pos])
			|| (was_char && ft_isalpha((*str)[pos])))
	{
		lex_add_char(buff, &sub, (*str)[pos]);
		(pos)++;
	}
	if (*len != pos)
		sub = sub ? ft_strjoin(sub, buff) : ft_strdup(buff);
	*len = pos - *len;
	return (sub);
}

static int	event_not_found(char **event)
{
	ft_putstr_fd("42sh: !", 2);
	ft_putstr_fd(*event, 2);
	ft_putstr_fd(": event not found\n", 2);
	ft_strdel(event);
	return (-2);
}

static int	find_expandable(char *str, int k)
{
	int		spqt;
	int		dbqt;

	dbqt = 0;
	spqt = 0;
	while (str[k])
	{
		if (str[k] == '\'' && (k <= 0 || str[k - 1] != '\\') && !dbqt)
			spqt = spqt * -1 + 1;
		if (str[k] == '"' && (k <= 0 || str[k - 1] != '\\') && !spqt)
			dbqt = dbqt * -1 + 1;
		if (str[k] == '!' && !spqt && !is_in_brac(k, str))
			return (k);
		k++;
	}
	return (-1);
}

int			lex_exclam(char **str)
{
	int		k;
	char	*old_sub;
	char	*sub;
	int		exclam;
	int		len;

	exclam = 0;
	k = -1;
	while ((*str)[++k])
	{
		if ((k = find_expandable(*str, k)) == -1)
			return (exclam);
		if ((old_sub = lex_following(str, k, &len)))
		{
			sub = hist_getexpend(&old_sub);
			if (!sub || !(exclam = 1))
				return (event_not_found(&old_sub));
			ft_strdel(&old_sub);
			lex_include(str, &sub, &k, len + 1);
		}
	}
	return (exclam);
}
