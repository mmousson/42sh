/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 14:52:12 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/27 17:42:56 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int		expand_manager(char **str, char ***arge, t_tok *token, int red)
{
	int	ret;

	if (!str || !(*str))
		return (0);
	if (expand_tilde(str))
		return (1);
	if ((ret = expand_shell_param(str, arge)))
		return (ret);
	if ((ret = expand_cmd_sub(str, arge, token)))
		return (0);
	if ((ret = expand_arithmetic(str, arge)))
		return (ret);
	if (token && (ret = expand_filename(str, token, red)))
		return (ret);
	if (expand_quote_removal(str))
		return (1);
	return (0);
}
