/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 14:52:12 by oboutrol          #+#    #+#             */
/*   Updated: 2019/05/29 13:38:00 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include <unistd.h>

int		expand_manager(char **str, char ***arge, __unused t_tok *token)
{
	int	ret;

	if (!str || !(*str))
		return (0);
	//if (expand_brace)
	//
	//if (expand_tilde)
	//
	if ((ret = expand_shell_param(str, arge)))
		return (ret);
	//if (expand_cmd_substitution)
	//
	if ((ret = expand_arithmetic(str, arge)))
		return (ret);
	//if (expand_word_splitting)
	//
	if (expand_filename(str, token))
		return (1);
	if (expand_quote_removal(str))
		return (1);
	return (0);
}
