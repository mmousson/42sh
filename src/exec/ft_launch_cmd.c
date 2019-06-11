/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 12:23:04 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/11 12:24:37 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "sh42.h"
#include "job_control_42.h"
#include "exe.h"
#include "libft.h"

uint8_t		g_prev_status;

void		ft_cmd_nf(char *str)
{
	ft_putstr_fd("42sh: command not found: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
}

void		ft_next_pipe(t_launch *cmd)
{
	cmd->next = ft_init_cmd(NULL);
}

static int	handle_logical_operators(void)
{
	if (g_current_ret != -1)
	{
		if ((g_prev_status == PIP + DBL && g_current_ret == 0)
				|| (g_prev_status == ESP + DBL && g_current_ret != 0))
			return (SKIP_JOB);
	}
	return (DONT_SKIP_JOB);
}

int			ft_launch_cmd(t_launch **cmd, char ***arge, int status)
{
	t_job	*job;
	int		fg;
	char	*tmp;

	if (handle_logical_operators() == DONT_SKIP_JOB)
	{
		if ((*cmd)->argv)
		{
			fg = status == ESP ? BACKGROUND_LAUNCH : FOREGROUND_LAUNCH;
			if (!(job = exe_load_job(*cmd, arge)))
				return (1);
			g_current_ret = job_launch(job, fg);
			utility_flush_tmp_vars();
			tmp = ft_itoa(g_current_ret);
			core_spec_var_setget(SPEC_QUESTION, tmp, SET);
			ft_strdel(&tmp);
		}
	}
	ft_free_cmd(*cmd);
	if (!(*cmd = ft_init_cmd(NULL)))
		exit(1);
	g_prev_status = status;
	return (0);
}
