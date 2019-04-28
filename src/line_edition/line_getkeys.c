/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_getkeys.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 03:46:52 by roliveir          #+#    #+#             */
/*   Updated: 2019/04/28 14:47:42 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"

static int			line_cpy_pst(char *str, int ret)
{
	if (line_isaltc(str, ret) && !g_env.mode->n_select)
		line_init_cpy();
	else if (line_isaltv(str, ret) && !g_env.mode->n_select)
		line_paste(g_env.cpy->str, 1);
	else
		return (0);
	return (1);
}

int					line_history(char *str, int ret)
{
	if (!ft_strcmp(g_env.tc->key[MUP], str)
			|| (str[0] == CTRLP && ret == 1))
		line_cursor_motion(MUP, 1);
	else if (!ft_strcmp(g_env.tc->key[MDOWN], str)
			|| (str[0] == CTRLN && ret == 1))
		line_cursor_motion(MDOWN, 1);
	else
		return (0);
	return (1);
}

int					line_motion(char *str, int ret)
{
	if (line_isleft(str, ret))
		line_cursor_motion(MLEFT, 1);
	else if (line_isright(str, ret))
		line_cursor_motion(MRIGHT, 1);
	else if (g_env.mode->mode[MNORMAL] && line_isaltf(str, ret))
		line_rjump();
	else if (g_env.mode->mode[MNORMAL] && line_isaltb(str, ret))
		line_ljump();
	else if (g_env.mode->mode[MNORMAL] && !ft_strcmp(str, UJUMP))
		line_cursor_motion(MLEFT, g_env.cm->term_x);
	else if (g_env.mode->mode[MNORMAL] && !ft_strcmp(str, DJUMP))
		line_cursor_motion(MRIGHT, g_env.cm->term_x);
	else if (line_ishome(str, ret))
		line_home(1);
	else if (line_isend(str, ret))
		line_end();
	else if (line_iscx(str, ret))
		line_cxjump();
	else
		return (0);
	return (1);
}

int					line_ascii(char *str, int ret)
{
	(void)ret;
	if (str[0] == '9')
		exit(0);
	if (str[0] <= 126 && str[0] >= 32)
		line_paste(str, 1);
	else
		return (0);
	return (1);
}

int					line_manager(char *str, int ret)
{
	if (str[0] == '\n' && ret == 1)
		return (line_return());
	else if (str[0] == CTRLD && ret == 1 && g_env.len == g_env.p_size + 1)
		return (line_ctrld());
	else if (line_ascii(str, ret))
		return (1);
	else if (line_del(str, ret))
		return (1);
	else if (line_motion(str, ret))
		return (1);
	else if (line_cpy_pst(str, ret))
		return (1);
	else if (line_history(str, ret))
		return (1);
	else if (line_vi_tmp(str))
		return (1);
	return (1);
}
