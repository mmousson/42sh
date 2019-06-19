/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 12:06:58 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/17 15:38:01 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <signal.h>
#include "sh42.h"
#include "job_control_42.h"
#include "line_edition.h"

/*
**	==================== BUITLIN COMMAND ====================
**	The exit utility shall cause the shell to exit from its current execution
**	environment with the exit status specified by the unsigned dec. integer n
**	If the current execution environment is a subshell environment, the shell
**	shall exit from the subshell environment with the specified exit status
**	and continue in the environment from which that subshell environment
**	was invoked; otherwise, the shell utility shall terminate with the
**	specified exit status. If n is specified, but its value is not between
**	0 and 255 inclusively, the exit status is undefined.
**
**	Return Value:
**	FG_JOB_FOUND (0) -> The job specified by 'jobspec' was correctly found and
**		resumed
**	FG_NO_SUCH_JOB (1) -> No job corresponding to 'jobspec' was found, nothing
**		was sent to foreground, and the shell still has control over terminal
*/

static void	blt_exit_select_argument(int argc, char **argv)
{
	if (argc == 2)
	{
		if (ft_valid_to_atoi(argv[1]))
			exit(ft_atoi(argv[1]));
		else
		{
			ft_putstr_fd("42sh: exit: ", STDERR_FILENO);
			ft_putstr_fd(argv[1], STDERR_FILENO);
			ft_putendl_fd(": numeric argument required", STDERR_FILENO);
			exit(2);
		}
	}
	else
		exit(g_last_ret);
}

static void	blt_exit_free_and_kill_jobs(void)
{
	time_t		seconds;

	seconds = time(NULL) + (time_t)1;
	job_signal_all_processes(SIGTERM);
	while (time(NULL) < seconds)
		;
	job_signal_all_processes(SIGKILL);
}

int			blt_exit(int argc, char **argv, char ***env)
{
	(void)env;
	if (argc > 2)
	{
		ft_putendl_fd("42sh: exit: too many arguments", STDERR_FILENO);
		return (1);
	}
	else
	{
		ft_del_words_tables(g_env.env);
		if (g_env.isatty)
		{
			sh_switch_term(1);
			close(g_env.t_fd);
		}
		line_delenv();
		core_free_shell_spec_vars_list();
		utility_purge_hash_table();
		utility_free_alias_list();
		utility_free_shell_vars_list();
		blt_exit_free_and_kill_jobs();
		blt_exit_select_argument(argc, argv);
	}
	return (0);
}
