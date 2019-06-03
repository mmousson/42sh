/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_matching.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 08:36:00 by hben-yah          #+#    #+#             */
/*   Updated: 2019/06/03 15:41:02 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"
#include "libft.h"

int		is_matching_asterisk(t_globtok *tok, char *file)
{
	if (*file != '/' && is_file_matching_pattern(tok->next, file))
		return (1);
	while (*file && *file != '/')
	{
		++file;
		if (is_file_matching_pattern(tok->next, file))
			return (1);
	}
	return (0);
}

int		is_matching_question(t_globtok *tok, char *file)
{
	if (*file && *file != '/' && ((!*(file + 1) && !tok->next)
		|| is_file_matching_pattern(tok->next, file + 1)))
		return (1);
	return (0);
}

int		is_matching_const(t_globtok *tok,
	t_str_token *tkn, char *file)
{
	if (ft_strnequ(tkn->value, file, tkn->len))
		return (is_file_matching_pattern(tok->next, file + tkn->len));
	return (0);
}

int		is_matching_range(t_globtok *tok,
	t_rng_token *tkn, char *file)
{
	if ((!tkn->negative && tkn->allow[(unsigned char)*file])
		|| (tkn->negative && !tkn->allow[(unsigned char)*file]))
		return (is_file_matching_pattern(tok->next, file + 1));
	return (0);
}
