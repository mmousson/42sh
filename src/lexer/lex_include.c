/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_include.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 10:52:30 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/09 20:20:35 by oboutrol         ###   ########.fr       */
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

int		lex_reline(t_stat *stat, t_tok **token, char buff[BUF])
{
	stat->old_status = 0;
	stat->k = -1;
	stat->status = 0;
	ft_strdel(&stat->load);
	ft_bzero(buff, BUF);
	lex_free_token(*token);
	*token = lex_init_token();
	return (1);
}
