/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_foreground.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 09:03:08 by mmousson          #+#    #+#             */
/*   Updated: 2019/07/03 18:44:03 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "line_edition.h"
#include "job_control_42.h"

/*
**	Function sending a job to the foreground
**	First we put the launched job in the 'foreground' process group
**	(with tcsetpgrp)
**	If we are continuing a stopped job, send it a SIGCONT signal to wake it up
**	Then, we must wait for said job to complete or to stop
**	Once this is done, we give back to the shell control of the terminal by
**	putting it back in the 'foreground' process group
**	Finally, we restore the terminal configuration saved in the extern variable
**
**	Arguments:
**	job -> A pointer to the Data-Structure holding the informations about
**		the job that's about to be launched (or continued)
**	must_continue -> boolean value telling us whether we should wake upthe job
**		pointed by 'job'
**
**	Return Value: The return value of the last process in the job's pipeline
**		loop
*/

int	job_send_to_foreground(t_job *job, int must_continue)
{
	int	ret;

	if (job->pgid > 0 && (getpgrp() == tcgetpgrp(STDIN_FILENO)))
		tcsetpgrp(STDIN_FILENO, job->pgid);
	if (must_continue == CONTINUE_JOB)
	{
		tcsetattr(STDIN_FILENO, TCSADRAIN, &job->tmodes);
		ft_putstr_fd("Send Job '", STDERR_FILENO);
		ft_putstr_fd(job->command, STDERR_FILENO);
		ft_putendl_fd("' to foreground", STDERR_FILENO);
		if (kill(-(job->pgid), SIGCONT) == -1)
		{
			ft_putstr_fd("Couldn't wake up the job: ", STDERR_FILENO);
			ft_putendl_fd(job->command, STDERR_FILENO);
			exit(126);
		}
	}
	ret = job_wait_completion(job, job->first_process);
	if (!g_subshell)
	{
		tcsetpgrp(STDIN_FILENO, g_shell_proc_group_id);
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &shell_term_conf);
	}
	return (ret);
}
