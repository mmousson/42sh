/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:46:23 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/30 11:02:19 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

static int		vi_nextcommand(char *str, int ret)
{
	if (vi_motion(str, ret))
		return (1);
	else if (vi_delete(str, ret))
		return (1);
	else if (vi_yank(str, ret))
		return (1);
	else if (vi_paste(str, ret))
		return (1);
	else if (vi_undo(str, ret))
		return (1);
	else
		return (0);
	vi_reset_count(str);
	return (1);
}

int				vi_command(char *str, int ret)
{
	if (str[0] == 27 && ret == 1)
		return (vi_reset_mode(0, 1, 0) + 1);
	if (vi_get_count(str)
		|| vi_get_prior_flag(str, ret))
		return (1);
	if (vi_insert(str, ret))
		return (1);
	else if (vi_history(str, ret))
		return (1);
	else if (str[0] == '#' && ret == 1)
		return (vi_hash_insert());
	else if (vi_visual(str, ret))
		return (1);
	else if (vi_nextcommand(str, ret))
		return (1);
	return (vi_reset_mode(0, 1, 0) + 1);
}
