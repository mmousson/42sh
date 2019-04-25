/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 20:11:08 by oboutrol          #+#    #+#             */
/*   Updated: 2019/04/25 11:16:21 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

int				ft_lex(char **str, t_env *env, char ***arge)
{
	t_tok		*token;
	t_stat		*stat;
	char		buff[BUF];

	(void)arge;
	if (!str || !(*str))
		return (0);
	if (!(token = ft_init_token()))
		return (1);
	if (!(stat = ft_init_stat()))
		return (1);
	buff[0] = '\0';
	while (stat->status != EN)
	{
		stat->cha = (*str)[stat->k];
		stat->ch = ft_get_ch(stat->cha);
		stat->old_status = stat->status;
		stat->status = ft_get_next_state(stat->status, stat->ch);
//		ft_step_lex(stat);
		if (stat->status != EN)
		{
			if (proc(stat, buff, token) == -1)
				ft_more(stat, str);
		}
		(stat->k)++;
	}
	ft_pars(token, arge, env);
	return (0);
}
