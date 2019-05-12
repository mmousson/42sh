/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_background.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 09:03:36 by mmousson          #+#    #+#             */
/*   Updated: 2019/05/12 18:48:16 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "sh42.h"
#include "libft.h"
#include "job_control_42.h"

/*
**	This functions does nothing when starting a job
**	Putting a job in background is simply done by not putting it
**	in the foreground
**	If it must wake up a job, however, simply send it a SIGCONT signal
**	and exit with an error message if it fails
**	If it succeeds, then set the Shell's Special Variable (!) to the pgid of
**	of the waking up Job
**
**	Arguments:
**	job -> A pointer to the Data-Structure holding the informations about
**		the job that's about to be launched (or continued)
**	must_continue -> boolean value telling us whether we should wake upthe job
**		pointed by 'job'
**
**	Return Value: Always 0
*/

int	job_send_to_background(t_job *job, int must_continue)
{
	char	*tmp;

	if (must_continue == CONTINUE_JOB)
	{
		if (kill(-(job->pgid), SIGCONT) == -1)
		{
			ft_putstr_fd("Couldn't wake up the job: ", STDERR_FILENO);
			ft_putendl_fd(job->command, STDERR_FILENO);
			exit(126);
		}
		tmp = ft_itoa(job->pgid);
		core_spec_var_setget(SPEC_EXCLAMATION, tmp, SET);
		ft_strdel(&tmp);
		ft_putstr_fd("\nSend Job '", STDERR_FILENO);
		ft_putstr_fd(job->command, STDERR_FILENO);
		ft_putendl_fd("' to background", STDERR_FILENO);
	}
	return (0);
}
