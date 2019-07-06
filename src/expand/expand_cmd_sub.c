/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd_sub.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 17:29:40 by oboutrol          #+#    #+#             */
/*   Updated: 2019/07/06 07:26:16 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int			expand_cmd_sub(char **str, char ***arge, t_tok *token)
{
	char	**tab;
	t_tok	*end;
	int		k;
	int		ret;

	if (!token)
		return (0);
	end = token->next;
	if (!str || !(*str) || !(*str)[0])
		return (0);
	ret = job_command_substitution(str, arge);
	if (!(*str) || !(*str[0]) || !(tab = ft_strsplit(*str, '\n')))
		return (0);
	free(*str);
	*str = tab[0];
	k = 0;
	while (tab[++k])
	{
		token->next = new_token_space();
		token = token->next;
		token->next = new_token_char(tab[k]);
		token = token->next;
	}
	free(tab);
	token->next = end;
	return (ret);
}
