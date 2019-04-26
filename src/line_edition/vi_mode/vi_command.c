/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:46:23 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/26 12:59:43 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"
#include "libft.h"

static int		ft_vi_nextcommand(char *str, int ret)
{
	if (ft_vi_motion(str, ret))
		return (1);
	else if (ft_vi_delete(str, ret))
		return (1);
	else if (ft_vi_yank(str, ret))
		return (1);
	else if (ft_vi_paste(str, ret))
		return (1);
	else if (ft_vi_undo(str, ret))
		return (1);
	else
		return (0);
	ft_reset_count(str);
	return (1);
}

int				ft_vi_command(char *str, int ret)
{
	ft_init_undo();
	if (str[0] == 27 && ret == 1)
		return (ft_reset_mode(0, 1, 0) + 1);
	if (ft_get_count(str)
		|| ft_get_prior_flag(str))
		return (1);
	else if (ft_vi_insert(str, ret))
		return (1);
	else if (ft_vi_history(str, ret))
		return (1);
	else if (str[0] == '#' && ret == 1)
		return (ft_hash_insert());
	else if (ft_vi_visual(str, ret))
		return (1);
	else if (ft_vi_nextcommand(str, ret))
		return (1);
	return (ft_reset_mode(0, 1, 0) + 1);
}
