/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 09:03:36 by mmousson          #+#    #+#             */
/*   Updated: 2019/04/08 12:37:12 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "libft.h"
#include "job_control_42.h"

/*
**	This functions does nothing when starting a job
**	Putting a job in background is simply done by not putting it
**	in the foreground
**	If it must wake up a job, however, simply send it a SIGCONT signal
**	and exit with an error message if it fails
**
**	Arguments:
**	job -> A pointer to the Data-Structure holding the informations about
**		the job that's about to be launched (or continued)
**	must_continue -> boolean value telling us whether we should wake upthe job
**		pointed by 'job'
**
**	Return Value: Always 0
*/

int	send_job_to_background(t_job *job, int must_continue)
{
	if (must_continue == CONTINUE_JOB)
	{
		if (kill(-(job->pgid), SIGCONT) == -1)
		{
			ft_putstr_fd("Couldn't wake up the job: ", STDERR_FILENO);
			ft_putendl_fd(job->command, STDERR_FILENO);
			exit(126);
		}
	}
	return (0);
}
