/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_builtin_redirect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 16:51:35 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/07 15:34:01 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "sh42.h"
#include "job_control_42.h"

/*
**	Function used to setup builtin I/O channels redirections when they are
**	alone in a pipeline loop
**	If a channel is being redirected, its original File Descriptor is saved
**		 in its counterpart in 'builtin_bkp' struct
**
**	Arguments:
**	proc -> A pointer to the Data-Structure holfding informations about the
**		builtin process
**
**	Return Value: NONE
*/

void	job_builtin_redirect(t_process *proc)
{
	t_lstfd	*fds;

	fds = proc->lstfd;
	while (fds != NULL)
	{
		(void)fds;
		fds = fds->next;
	}
}

/*
**	Function used to restore builtin I/O channels redirections when they are
**	alone in a pipeline loop
**	It is done by checking if a field in 'builtin_bkp' corresponding to an I/O
**	channel is different than (-1), which is the default value assigned to
**	those field when the process Data-Structure is loaded
**
**	Arguments:
**	proc -> A pointer to the Data-Structure holfding informations about the
**		builtin process
**
**	Return Value: NONE
*/

void	job_builtin_restore(t_process *proc)
{
	if (proc->builtin_bkp.input != -1)
	{
		dup2(proc->builtin_bkp.input, STDIN_FILENO);
		close(proc->builtin_bkp.input);
	}
	if (proc->builtin_bkp.output != -1)
	{
		dup2(proc->builtin_bkp.output, STDOUT_FILENO);
		close(proc->builtin_bkp.output);
	}
	if (proc->builtin_bkp.error != -1)
	{
		dup2(proc->builtin_bkp.error, STDERR_FILENO);
		close(proc->builtin_bkp.error);	
	}
}
