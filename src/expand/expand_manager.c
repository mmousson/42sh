/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 14:52:12 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/25 11:27:28 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

#include "libft.h"
int		expand_manager(char ***argv, char ***arge)
{
	int	ret;

	if (!argv || !(*argv))
		return (1);
	//if (expand_brace)
	//
	//if (expand_tilde)
	//
	if ((ret = expand_shell_param(argv, arge)))
		return (ret);
	//if (expand_cmd_substitution)
	//
	//if (expand_arithmetics)
	//
	//if (expand_word_splitting)
	//
	//if (expand_filename)
	//
	if (expand_quote_removal(argv))
		return (1);
	return (0);
}
