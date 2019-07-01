/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_bracket.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 11:41:42 by oboutrol          #+#    #+#             */
/*   Updated: 2019/07/01 14:43:59 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int			is_esc(char c)
{
	static int	sq;
	static int	dq;
	static int	bs;

	if (!c)
	{
		sq = 0;
		dq = 0;
		bs = 0;
	}
	if (!bs && c == '\\')
		bs = 1;
	if (!bs && !dq)
		sq = c == '\'' ? -sq + 1 : sq;
	if (!bs && !sq)
		dq = c == '"' ? -dq + 1 : dq;
	return (sq || dq || bs);
}

int			pars_bracket(t_tok **tok)
{
	char	*line;
	int		k;
	char	end;

	if (!(*tok))
		return (0);
	line = (*tok)->content;
	end = line[0] == '(' ? ')' : 0;
	is_esc(0);
	if (!end)
		end = line[0] == '{' ? '}' : 0;
	k = -1;
	while (line[++k] && line[k] != end)
		if (!end && !is_esc(line[k]) && (line[k] == '{' || line [k] == '('))
		{
			ft_putstr_fd("42sh: Parse Error\n", 2);
			return (1);
		}
	if (k >= 0 &&  line[k] && line[k +1])
	{
		ft_putstr_fd("42sh: Parse Error\n", 2);
		return (1);
	}
	return (0);
}
