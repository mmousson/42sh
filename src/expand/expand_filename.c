/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_filename.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 07:36:36 by akarasso          #+#    #+#             */
/*   Updated: 2019/05/28 17:35:01 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"
#include "libft.h"
#include "pars.h"
#include "lex.h"

int			expand_filename(char **path, t_tok *token)
{
	char	**files;
	int		k;
	t_tok	*end;

	end = token->next;
	if (!path || !(files = sh_glob(*path)))
		return (0);
	free(*path);
	*path = files[0];
	k = 0;
	while (files[++k])
	{
		token->next = new_token_char(files[k]);
		token = token->next;
		if (files[k + 1])
		{
			token->next = new_token_space();
			token = token->next;
		}
	}
	token->next = end;
	return (0);
}
