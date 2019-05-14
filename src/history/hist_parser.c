/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 13:53:33 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/14 16:21:32 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

char		*hist_parsline(char *line)
{
	int		i;
	char	*newline;

	i = 0;
	newline = NULL;
	if (!line || !line[0] || !ft_isascii(line[0]))
		return (NULL);
	while (line[i] && line[i] != ';')
		i++;
	if (!line[i])
		return (NULL);
	i++;
	if (line[i] && !(newline = ft_strdup(&(line[i]))))
		sh_errorterm(TMALLOC);
	return (newline);
}
