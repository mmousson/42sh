/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 12:06:58 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/10 16:27:35 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
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

int					blt_exit(int argc, char **argv, char ***env)
{
	if (argc > 2)
	{
		ft_putendl_fd("42sh: exit: Too many arguments", STDERR_FILENO);
		return (1);
	}
	else
	{
		ft_del_words_tables(env);
		if (g_env.isatty)
		{
			sh_switch_term(1);
			close(g_env.t_fd);
		}
		line_delenv();
		core_free_shell_spec_vars_list();
		utility_free_alias_list();
		utility_free_shell_vars_list();
		exit(argc == 2 ? ft_atoi(argv[1]) : g_last_ret);
	}
	return (0);
}
