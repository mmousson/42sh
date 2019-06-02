/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 14:52:12 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/02 15:41:29 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include <unistd.h>

#include "libft.h"
int		expand_manager(char **str, char ***arge, t_tok *token)
{
	int	ret;

	if (!str || !(*str))
		return (0);
	//if (expand_brace)
	//
	if (expand_tilde(str))
		return (1);
	if ((ret = expand_shell_param(str, arge)))
		return (ret);
	//if (expand_cmd_substitution)
	//
	if ((ret = expand_arithmetic(str, arge)))
		return (ret);
	//if (expand_word_splitting)
	//
	//(void)token;
	if (expand_filename(str, token))
		return (1);
	if (expand_quote_removal(str))
		return (1);
	return (0);
}
