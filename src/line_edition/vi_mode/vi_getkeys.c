/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_getkeys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 16:16:24 by roliveir          #+#    #+#             */
/*   Updated: 2019/05/08 15:45:02 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

static int			vi_minsert(char *str, int ret)
{
	/*
<<<<<<< HEAD:src/line_edition/vi_mode/getvi_keys.c
	if (!ft_tmp(str))
		return (0);
	return (1);
}

static int			ft_minsert(char *str, int ret)
{
=======
>>>>>>> lex_pars:src/line_edition/vi_mode/vi_getkeys.c
*/
	if (str[0] == 27 && ret == 1)
		return (line_escap());
	if (str[0] == CTRLD && ret == 1 && g_env.len == g_env.p_size + 1)
		return (line_ctrld());
	else if (str[0] == 127 && ret == 1)
	{
		g_env.line = line_delchar(1);
		g_env.del = 1;
		line_cursor_motion(MLEFT, 1);
		g_env.del = 0;
	}
	else if (line_ascii(str, ret))
		return (1);
	else if (line_motion(str, ret))
		return (1);
	else if (line_history(str, ret))
		return (1);
	return (1);
}

int					line_vi(char *str, int ret)
{
	int				reset;

	reset = 1;
	if (str[0] == '\n' && ret == 1)
		return (line_return());
	if (g_env.mode->v_insert)
		return (vi_minsert(str, ret));
	else if (g_env.mode->v_command)
		reset = vi_command(str, ret);
	if (!reset)
		return (vi_reset_mode(1, 0, 0));
	return (1);
}
