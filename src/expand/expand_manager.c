/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 14:52:12 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/24 17:32:49 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int		expand_manager(char ***argv, char ***arge)
{
	if (!argv || !(*argv))
		return (1);
	//if (expand_brace)
	//
	//if (expand_tilde)
	//
	if (expand_shell_param(argv, arge))
		return (1);
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
