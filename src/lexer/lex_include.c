/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_include.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 10:52:30 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/15 19:15:46 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lex.h"

void	lex_include(char **str, char **sub, int start, int end)
{
	char	*str_start;
	char	*str_end;

	str_start = ft_strsub(*str, 0, start);
	str_end = ft_strdup(*str + end);
	if (sub)
		str_start = ft_strjoinf(str_start, *sub);
	free(*str);
	*str = ft_strjoin(str_start, str_end);
	ft_strdel(&str_start);
	ft_strdel(&str_end);
	ft_strdel(sub);
}
